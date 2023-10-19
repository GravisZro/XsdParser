#include "XsdParserCore.h"

#include <xsdelements/XsdElement.h>
#include <xsdelements/XsdSchema.h>
#include <xsdelements/XsdImport.h>
#include <xsdelements/XsdInclude.h>
#include <xsdelements/elementswrapper/UnsolvedReference.h>

ParserConfig XsdParserCore::m_config;
std::map<std::string_view, ConfigEntryData> XsdParserCore::m_parseMappers = m_config.getParseMappers();
StringMap XsdParserCore::m_xsdTypesToJava = m_config.getXsdTypesToJava();

/**
 * Verifies if a given {@link DOMNode} object, i.e. {@code node} is a xsd:schema node.
 * @param node The node to verify.
 * @return True if the node is a xsd:schema or xs:schema. False otherwise.
 */
bool XsdParserCore::isXsdSchema(pugi::xml_node node)
{
    std::string schemaNodeName = node.name();

    return schemaNodeName == XsdSchema::XSD_TAG ||
         schemaNodeName == XsdSchema::XS_TAG ||
         schemaNodeName == XsdSchema::TAG;
}

/**
 * @return A list of all the top level parsed xsd:elements by this class. It doesn't return any other elements apart
 * from xsd:elements. To access the whole element tree use {@link XsdParser#getResultXsdSchemas()}
 */
std::list<std::shared_ptr<XsdElement>> XsdParserCore::getResultXsdElements(void)
{
  std::list<std::shared_ptr<XsdElement>> rval;
  for(auto& schema : getResultXsdSchemas())
    for(auto& element : schema->getChildrenElements())
      rval.push_back(element);
  return rval;
}

/**
 * @return A {@link List} of all the {@link XsdSchema} elements parsed by this class. You can use the {@link XsdSchema}
 * instances to navigate through the whole element tree.
 */
std::list<std::shared_ptr<XsdSchema>> XsdParserCore::getResultXsdSchemas(void)
{
  std::list<std::shared_ptr<XsdSchema>> rval;
  for(auto& pair : m_parseElements)
    for(auto& element : pair.second)
      if(auto x = std::dynamic_pointer_cast<XsdSchema>(element); x)
        rval.push_back(x);
  return rval;
}

std::string getSubStringAfter(std::optional<std::string> input, const char target)
{
  assert(input);
  if(input->contains(target))
    return input->substr(input->find_last_of(target) + 1);
  return input.value();
}

std::shared_ptr<XsdSchema> findXsdSchema(const std::list<std::shared_ptr<ReferenceBase>>& haystack)
{
  for(auto& referenceBase : haystack)
    if(std::dynamic_pointer_cast<ConcreteElement>(referenceBase))
      if(auto x = std::dynamic_pointer_cast<XsdSchema>(referenceBase->getElement()); x)
        return x;
  return nullptr;
}

void XsdParserCore::resolveOtherNamespaceRefs(void)
{

  for(auto& schema : getResultXsdSchemas())
  {
    for(auto& xsdImport : schema->getChildrenImports())
      schema->resolveNameSpace(xsdImport->getNamespace(), xsdImport->getSchemaLocation());

    for(auto key : std::views::keys(schema->getNamespaces()))
      schema->resolveNameSpace(key, schema->getFileLocation());
  }

  for(auto& pair : m_parseElements)
  {
    auto& fileLocation = pair.first;
    std::shared_ptr<XsdSchema> xsdSchema = findXsdSchema(pair.second);

    auto ns = xsdSchema->getNamespaces();

    std::list<std::shared_ptr<UnsolvedReference>> unsolvedReferenceList;
    if(m_unsolvedElements.contains(fileLocation))
      for(auto& unsolvedElement : m_unsolvedElements.at(fileLocation))
        if(unsolvedElement->getRef().value_or("").contains(':'))
          unsolvedReferenceList.push_back(unsolvedElement);


    long startingUnsolvedReferenceListSize = 0;
    long currentUnsolvedReferenceListSize = unsolvedReferenceList.size();

    do
    {
      startingUnsolvedReferenceListSize = currentUnsolvedReferenceListSize;
      for (auto unsolvedReference : unsolvedReferenceList)
      {
        auto unsolvedElementNamespace = getSubStringAfter(unsolvedReference->getRef(), ':');

        if (ns.contains(unsolvedElementNamespace))
        {
          auto namespaceInfo = ns.at(unsolvedElementNamespace);
          std::list<std::shared_ptr<ReferenceBase>> importedElements;
          auto unsolvedElementSchema = unsolvedReference->getElement()->getXsdSchema();

          if (unsolvedElementSchema &&
              unsolvedElementSchema->getTargetNamespace() &&
              unsolvedElementSchema->getTargetNamespace() == namespaceInfo.getName())
            importedElements = unsolvedElementSchema->getElements();
          else
          {
            auto importedFileLocation = ns.at(unsolvedElementNamespace).getFile();
            if(m_parseElements.contains(importedFileLocation))
              importedElements = m_parseElements.at(importedFileLocation);
          }

          std::map<std::string, std::list<std::shared_ptr<NamedConcreteElement>>> concreteElementsMap;
          for(auto& concreteElement : importedElements)
            if(auto x = std::dynamic_pointer_cast<NamedConcreteElement>(concreteElement); x)
              concreteElementsMap[x->getName()].push_back(x);
          replaceUnsolvedImportedReference(concreteElementsMap, unsolvedReference, fileLocation);
        }
      }

      unsolvedReferenceList.clear();
      if(m_unsolvedElements.contains(fileLocation))
        for(auto& unsolvedElement : m_unsolvedElements.at(fileLocation))
          if(unsolvedElement->getRef().value_or("").contains(':'))
            unsolvedReferenceList.push_back(unsolvedElement);

      currentUnsolvedReferenceListSize = unsolvedReferenceList.size();
    } while (currentUnsolvedReferenceListSize != startingUnsolvedReferenceListSize);
  }
}


void XsdParserCore::replaceUnsolvedImportedReference(std::map<std::string, std::list<std::shared_ptr<NamedConcreteElement>>> concreteElementsMap,
                                                     std::shared_ptr<UnsolvedReference> unsolvedReference,
                                                     SchemaLocation fileLocation)
{
    std::list<std::shared_ptr<NamedConcreteElement>> concreteElements = concreteElementsMap.at(getSubStringAfter(unsolvedReference->getRef(), ':'));

    if(concreteElements.empty())
      storeUnsolvedItem(unsolvedReference);
    else
    {
        StringMap oldElementAttributes = unsolvedReference->getElement()->getAttributesMap();

        for (auto& concreteElement : concreteElements)
        {
            std::shared_ptr<NamedConcreteElement> substitutionElementWrapper = concreteElement;

            if (!unsolvedReference->isTypeRef())
            {
                std::shared_ptr<XsdNamedElements> substitutionElement = std::static_pointer_cast<XsdNamedElements>(
                                                                          concreteElement->getElement()->clone(oldElementAttributes,
                                                                          concreteElement->getElement()->getParent()));

                substitutionElementWrapper = std::static_pointer_cast<NamedConcreteElement>(ReferenceBase::createFromXsd(substitutionElement));
            }

            unsolvedReference->getParent()->replaceUnsolvedElements(substitutionElementWrapper);
        }

        m_unsolvedElements.at(fileLocation).remove(unsolvedReference);
    }
}



void XsdParserCore::resolveInnerRefs(void)
{
  auto fileNameList = std::views::keys(m_parseElements);
  std::map<SchemaLocation, bool> doneList;

  while(std::ranges::any_of(doneList, [](auto& pair) { return pair.second == false; }))
  {
    for(auto& pair : m_parseElements)
    {
      auto& fileLocation = pair.first;
      if (!doneList.at(fileLocation))
      {
        std::set<SchemaLocation> includedLocations;
        for(auto& referenceBase : pair.second)
          if(auto x = std::dynamic_pointer_cast<XsdInclude>(referenceBase->getElement());
             std::dynamic_pointer_cast<ConcreteElement>(referenceBase) && x)
            includedLocations.insert(x->getSchemaLocation());

        std::set<SchemaLocation> transitiveIncludes;

        for(auto& includedLocation : includedLocations)
          for(auto& pair : m_parseElements)
            if(pair.first == includedLocation)
            {
              for(auto& referenceBase : pair.second)
                if(auto x = std::dynamic_pointer_cast<XsdInclude>(referenceBase->getElement());
                   std::dynamic_pointer_cast<ConcreteElement>(referenceBase) && x)
                  transitiveIncludes.insert(x->getSchemaLocation());
              break;
            }

        includedLocations.merge(transitiveIncludes);
        for(auto& schema : getResultXsdSchemas())
          if(std::ranges::any_of(schema->getChildrenIncludes(),
                                 [fileLocation](auto& xsdInclude) -> bool { return xsdInclude->getSchemaLocation() == fileLocation; }))
            includedLocations.insert(schema->getFileLocation());

        std::list<std::shared_ptr<ReferenceBase>> includedElements = pair.second;

        for(auto& includedLocation : includedLocations)
        {
          if(m_parseElements.contains(includedLocation))
            includedElements.merge(m_parseElements.at(includedLocation));
          else
            for(auto& subpair : m_parseElements)
              if(subpair.first == includedLocation)
                includedElements.merge(subpair.second);
        }

        std::map<std::string, std::list<std::shared_ptr<NamedConcreteElement>>> concreteElementsMap;
        for(auto& concreteElement : includedElements)
          if(auto x = std::dynamic_pointer_cast<NamedConcreteElement>(concreteElement); x)
            concreteElementsMap[x->getName()].push_back(x);

        std::list<std::shared_ptr<UnsolvedReference>> unsolvedReferenceList;
        if(m_unsolvedElements.contains(fileLocation))
          for(auto& unsolvedElement : m_unsolvedElements.at(fileLocation))
          {
            assert(unsolvedElement->getRef());
            if(!unsolvedElement->getRef()->contains(":"))
              unsolvedReferenceList.push_back(unsolvedElement);
          }

        struct progession_t
        {
          std::size_t startingSize = 0;
          std::size_t currentSize = 0;
          void setCurrentSize(std::size_t newSize) noexcept
          {
            startingSize = currentSize;
            currentSize = newSize;
          }
          bool progressMade(void) const
            { return startingSize != currentSize; }
        } progressTracker;

        bool unsolvedReferenceListNotEmpty = false;
        do
        {
          std::ranges::remove_if(unsolvedReferenceList,
                                 [this](auto& u)
          { return std::ranges::any_of(m_parserUnsolvedElementsMap,
                                       [u](auto u1) { return u == u1->getUnsolvedReference(); });
          });
          unsolvedReferenceListNotEmpty = !unsolvedReferenceList.empty();

          for (auto& unsolvedReference : unsolvedReferenceList)
            replaceUnsolvedReference(concreteElementsMap, unsolvedReference, fileLocation);

          unsolvedReferenceList.clear();
          if(m_unsolvedElements.contains(fileLocation))
            for(auto& unsolvedElement : m_unsolvedElements.at(fileLocation))
              if(!unsolvedElement->getRef()->contains(":"))
                unsolvedReferenceList.push_back(unsolvedElement);

          progressTracker.setCurrentSize(unsolvedReferenceList.size()); // update progress
        } while(progressTracker.progressMade());

        doneList[fileLocation] = true;

        if (unsolvedReferenceListNotEmpty)
          for(auto& includedFile : includedLocations)
            if (!std::ranges::contains(fileNameList, includedFile))
              doneList[includedFile] = false;
      }
    }
  }
}




/**
 * Replaces a single {@link UnsolvedReference} object, with the respective {@link NamedConcreteElement} object. If
 * there isn't a {@link NamedConcreteElement} object to replace the {@link UnsolvedReference} object, information
 * is stored informing the user of this Project of the occurrence.
 * @param concreteElementsMap The map containing all named concreteElements.
 * @param unsolvedReference The unsolved reference to solve.
 */
void XsdParserCore::replaceUnsolvedReference(std::map<std::string, std::list<std::shared_ptr<NamedConcreteElement>>> concreteElementsMap,
                                             std::shared_ptr<UnsolvedReference> unsolvedReference,
                                             SchemaLocation fileLocation)
{
  assert(unsolvedReference->getRef());
  assert(concreteElementsMap.contains(unsolvedReference->getRef().value()));

  std::list<std::shared_ptr<NamedConcreteElement>> concreteElements = concreteElementsMap.at(unsolvedReference->getRef().value());

    if (concreteElements.empty())
      storeUnsolvedItem(unsolvedReference);
    else
    {
        auto oldElementAttributes = unsolvedReference->getElement()->getAttributesMap();

        for (auto& concreteElement : concreteElements) {
            std::shared_ptr<NamedConcreteElement> substitutionElementWrapper;

            if (unsolvedReference->isTypeRef())
              substitutionElementWrapper = concreteElement;
            else
            {
                std::shared_ptr<XsdNamedElements> substitutionElement =
                    std::static_pointer_cast<XsdNamedElements>(
                      concreteElement->getElement()->clone(
                        oldElementAttributes,
                        concreteElement->getElement()->getParent()));

                substitutionElementWrapper =
                    std::static_pointer_cast<NamedConcreteElement>(
                      ReferenceBase::createFromXsd(
                        substitutionElement));
            }

            unsolvedReference->getParent()->replaceUnsolvedElements(substitutionElementWrapper);
        }

        assert(m_unsolvedElements.contains(fileLocation));
        m_unsolvedElements.at(fileLocation).remove(unsolvedReference);
    }
}



/**
 * Saves an occurrence of an element which couldn't be resolved in the {@link XsdParser#replaceUnsolvedReference}
 * method, which can be accessed at the end of the parsing process in order to verify if were there were any
 * references that couldn't be solved.
 * @param unsolvedReference The unsolved reference which couldn't be resolved.
 */
void XsdParserCore::storeUnsolvedItem(std::shared_ptr<UnsolvedReference> unsolvedReference)
{
    if (m_parserUnsolvedElementsMap.empty())
        m_parserUnsolvedElementsMap.push_back(std::make_shared<UnsolvedReferenceItem>(unsolvedReference));
    else
    {
      std::shared_ptr<UnsolvedReferenceItem> innerEntry;

      for(auto& unsolvedReferenceObj : m_parserUnsolvedElementsMap)
        if(unsolvedReference->getRef() &&
           unsolvedReferenceObj->getUnsolvedReference()->getRef() == unsolvedReference->getRef())
        {
          innerEntry = unsolvedReferenceObj;
          break;
        }

      if (innerEntry)
        innerEntry->getParents().push_back(unsolvedReference->getParent());
      else
        m_parserUnsolvedElementsMap.push_back(std::make_shared<UnsolvedReferenceItem>(unsolvedReference));
    }
}



/**
 * Adds an {@link UnsolvedReference} object to the {@link XsdParser#unsolvedElements} list which should be solved
 * at a later time in the parsing process.
 * @param unsolvedReference The unsolvedReference to add to the unsolvedElements list.
 */
void XsdParserCore::addUnsolvedReference(std::shared_ptr<UnsolvedReference> unsolvedReference)
{
    std::shared_ptr<XsdSchema> schema;
    try
    {
      schema = XsdAbstractElement::getXsdSchema(unsolvedReference->getElement(), {});
    }
    catch(ParentAvailableException& e) { }

    std::list<std::shared_ptr<UnsolvedReference>> unsolved;
    if(schema)
    {
      if(m_unsolvedElements.contains(schema->getFileLocation()))
        unsolved = m_unsolvedElements.at(schema->getFileLocation());
    }
    else if(m_unsolvedElements.contains(m_currentFile))
      unsolved = m_unsolvedElements.at(m_currentFile);

    unsolved.push_back(unsolvedReference);
}


/**
 * Adds a new file to the parsing queue. This new file appears by having xsd:import or xsd:include tags in the
 * original file to parse.
 * @param schemaLocation A new file path of another XSD file to parse.
 */
void XsdParserCore::addLocationToParse(SchemaLocation schemaLocation)
{
  m_schemaLocations.insert(schemaLocation);
  for(auto& location : schemaLocation)
    m_schemaLocationsMap.emplace(location, m_currentFile);
}
