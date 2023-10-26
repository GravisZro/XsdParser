#include "XsdParserCore.h"

#include <xsdelements/XsdElement.h>
#include <xsdelements/XsdSchema.h>
#include <xsdelements/XsdImport.h>
#include <xsdelements/XsdInclude.h>

#include <algorithm>

ParserConfig XsdParserCore::m_config;
std::map<std::string_view, ConfigEntryData> XsdParserCore::m_parseMappers = m_config.getParseMappers();
StringMap XsdParserCore::m_xsdTypesToCpp = m_config.getXsdTypesToCpp();

/**
 * Verifies if a given {@link DOMNode} object, i.e. {@code node} is a xsd:schema node.
 * @param node The node to verify.
 * @return True if the node is a xsd:schema or xs:schema. False otherwise.
 */
bool XsdParserCore::isXsdSchema(pugi::xml_node node)
{
    std::string schemaNodeName = node.name();

    return schemaNodeName == TAG<XsdSchema>::xsd ||
         schemaNodeName == TAG<XsdSchema>::xs ||
         schemaNodeName == TAG<XsdSchema>::id;
}

/**
 * @return A list of all the top level parsed xsd:elements by this class. It doesn't return any other elements apart
 * from xsd:elements. To access the whole element tree use {@link XsdParser#getResultXsdSchemas()}
 */
std::list<std::shared_ptr<XsdAbstractElement>> XsdParserCore::getResultXsdElements(void)
{
  std::list<std::shared_ptr<XsdAbstractElement>> rval;
  for(auto& schema : getResultXsdSchemas())
    for(auto& element : schema->getXsdElements())
      rval.push_back(element);
  return rval;
}

/**
 * @return A list of all the top level parsed xsd:elements by this class. It doesn't return any other elements apart
 * from xsd:elements. To access the whole element tree use {@link XsdParser#getResultXsdSchemas()}
 */
std::list<std::shared_ptr<XsdElement>> XsdParserCore::getResultChildrenElements(void)
{
  std::list<std::shared_ptr<XsdElement>> rval;
  for(auto& schema : getResultXsdSchemas())
    for(auto& element : schema->getChildren<XsdElement>())
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
      if(auto x = std::dynamic_pointer_cast<XsdSchema>(element->getElement()); x)
        rval.push_back(x);
  return rval;
}


/**
 * @fn getSubStringBefore
 * @oldcode (Java)
 * SOMESTRING.substring(0, SOMESTRING.indexOf(TARGET));
 * @note VERIFIED
 */
std::string getSubStringBefore(std::optional<std::string> input, const char target)
{
  assert(input);
  if(input->contains(target))
    return input->substr(0, input->find_first_of(target));
  return std::string();
}

std::string getSubStringAfter(std::optional<std::string> input, const char target)
{
  assert(input);
  if(input->contains(target))
    return input->substr(input->find_last_of(target) + 1);
  return input.value();
}


/**
 * @fn findXsdSchema
 * @param fileLocationElements Java: parseElements.get(fileName)
 * @oldcode (Java)
 * XsdSchema xsdSchema = parseElements.get(fileName)
 *                                   .stream()
 *                                   .filter(referenceBase -> referenceBase instanceof ConcreteElement && referenceBase.getElement() instanceof XsdSchema)
 *                                   .map(referenceBase -> (XsdSchema) referenceBase.getElement())
 *                                   .findFirst()
 *                                   .get();
 * @note VERIFIED
 */
std::shared_ptr<XsdSchema> findXsdSchema(const std::list<std::shared_ptr<ReferenceBase>>& fileLocationElements)
{
  for(auto& referenceBase : fileLocationElements)
    if(std::dynamic_pointer_cast<ConcreteElement>(referenceBase))
      if(auto x = std::dynamic_pointer_cast<XsdSchema>(referenceBase->getElement()); x)
        return x;
  return nullptr;
}

/**
 * @fn getUnsolvedReferenceList
 * @param fileLocation Java: fileName
 * @param unsolvedElements Java: unsolvedElements
 * @oldcode (Java)
 * List<UnsolvedReference> unsolvedReferenceList = unsolvedElements
 *         .getOrDefault(fileName, new ArrayList<>())
 *         .stream()
 *         .filter(unsolvedElement -> unsolvedElement.getRef().contains(":"))
 *         .collect(Collectors.toList());
 * @note VERIFIED
 */
auto getUnsolvedReferenceList(
    const SchemaLocation& fileLocation,
    const std::map<SchemaLocation, std::list<std::shared_ptr<UnsolvedReference>>>& unsolvedElements)
{
  std::list<std::shared_ptr<UnsolvedReference>> unsolvedReferenceList; // returned type
  if(unsolvedElements.contains(fileLocation))
    for(auto& unsolvedElement : unsolvedElements.at(fileLocation))
      if(unsolvedElement->getRef().value_or("").contains(':'))
        unsolvedReferenceList.push_back(unsolvedElement);
  return unsolvedReferenceList;
}

/**
 * @fn getConcreteImportedElements
 * @param importedElements Java: importedElements
 * @oldcode (Java)
 * Map<String, List<NamedConcreteElement>> concreteElementsMap =
 *         importedElements.stream()
 *                  .filter(concreteElement -> concreteElement instanceof NamedConcreteElement)
 *                  .map(concreteElement -> (NamedConcreteElement) concreteElement)
 *                  .collect(groupingBy(NamedConcreteElement::getName));
 * @note VERIFIED
 */
auto getConcreteImportedElements(const std::list<std::shared_ptr<ReferenceBase>>& importedElements)
{
  std::map<std::string, std::list<std::shared_ptr<NamedConcreteElement>>> concreteElementsMap;
  for(auto& concreteElement : importedElements)
    if(auto x = std::dynamic_pointer_cast<NamedConcreteElement>(concreteElement); x)
      concreteElementsMap[x->getName()].push_back(x);
  return concreteElementsMap;
}

/**
 * @fn resolveOtherNamespaceRefs
 * @note VERIFIED
 */
void XsdParserCore::resolveOtherNamespaceRefs(void)
{
  for(auto& schema : getResultXsdSchemas())
  {
    for(const auto& xsdImport : schema->getChildren<XsdImport>())
      schema->resolveNameSpace(xsdImport->getNamespace(), xsdImport->getSchemaLocation());

    for(const auto& pair : schema->getNamespaces())
      schema->resolveNameSpace(pair.first, schema->getFileLocation());
  }

  for(auto& pair : m_parseElements)
  {
    auto& fileLocation = pair.first;
    std::shared_ptr<XsdSchema> xsdSchema = findXsdSchema(pair.second);

    std::size_t startingUnsolvedReferenceListSize = 0;
    auto ns = xsdSchema->getNamespaces();

    std::list<std::shared_ptr<UnsolvedReference>> unsolvedReferenceList;
    do
    {
      startingUnsolvedReferenceListSize = unsolvedReferenceList.size();
      unsolvedReferenceList = getUnsolvedReferenceList(fileLocation, m_unsolvedElements);

      for (auto unsolvedReference : unsolvedReferenceList)
      {
        std::string unsolvedElementNamespace = getSubStringBefore(unsolvedReference->getRef(), ':');

        if (unsolvedElementNamespace.size() &&
            ns.contains(unsolvedElementNamespace))
        {
          const NamespaceInfo& unsolvedNamespaceInfo = ns.at(unsolvedElementNamespace);
          std::list<std::shared_ptr<ReferenceBase>> importedElements;
          auto unsolvedElementSchema = unsolvedReference->getElement()->getXsdSchema();

          if (unsolvedElementSchema &&
              unsolvedElementSchema->getTargetNamespace() &&
              unsolvedElementSchema->getTargetNamespace() == unsolvedNamespaceInfo.getName())
            importedElements = unsolvedElementSchema->getElements();
          else
          {
            // Note: SchemaLocation results in a radical code reduction here
            assert(m_parseElements.contains(ns.at(unsolvedElementNamespace).getFile()));
            importedElements = m_parseElements.at(ns.at(unsolvedElementNamespace).getFile());
          }

          auto concreteElementsMap = getConcreteImportedElements(importedElements);
          replaceUnsolvedImportedReference(concreteElementsMap, unsolvedReference, fileLocation);
        }
      }
    } while (startingUnsolvedReferenceListSize != unsolvedReferenceList.size());
  }
}

/**
 * @fn replaceUnsolvedImportedReference
 * @note VERIFIED
 */
void XsdParserCore::replaceUnsolvedImportedReference(
    std::map<std::string, std::list<std::shared_ptr<NamedConcreteElement>>> concreteElementsMap,
    std::shared_ptr<UnsolvedReference> unsolvedReference,
    SchemaLocation fileLocation)
{
    std::list<std::shared_ptr<NamedConcreteElement>> concreteElements =
        concreteElementsMap.at(getSubStringAfter(unsolvedReference->getRef(), ':'));

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


/**
 * @fn getIncludedLocations
 * @param fileLocationElements Java: parseElements.get(fileName)
 * @oldcode (Java)
 * List<String> includedFiles =
 *          parseElements.get(fileName)
 *                  .stream()
 *                  .filter(referenceBase -> referenceBase instanceof ConcreteElement && referenceBase.getElement() instanceof XsdInclude)
 *                  .map(referenceBase -> (((XsdInclude) referenceBase.getElement()).getSchemaLocation()))
 *                  .collect(Collectors.toList());
 * @note VERIFIED
 */
auto getIncludedLocations(const std::list<std::shared_ptr<ReferenceBase>>& fileLocationElements)
{
  std::set<SchemaLocation> includedLocations;
  for(auto& referenceBase : fileLocationElements)
    if(auto x = std::dynamic_pointer_cast<XsdInclude>(referenceBase->getElement());
       std::dynamic_pointer_cast<ConcreteElement>(referenceBase) && x)
      includedLocations.insert(x->getSchemaLocation());
  return includedLocations;
}


/**
 * @fn getTransitiveIncludes
 * @param locations Java: parseElements.get(fullIncludedFileName)
 * @oldcode (Java)
 *  parseElements.get(fullIncludedFileName)
 *          .stream()
 *          .filter(referenceBase -> referenceBase instanceof ConcreteElement && referenceBase.getElement() instanceof XsdInclude)
 *          .map(referenceBase -> ( ((XsdInclude) referenceBase.getElement()) .getSchemaLocation())
 * @note VERIFIED
 */

auto getTransitiveIncludes(const std::list<std::shared_ptr<ReferenceBase>>& locations)
{
  std::set<SchemaLocation> transitiveIncludes;
  for(auto& referenceBase : locations)
    if(auto x = std::dynamic_pointer_cast<XsdInclude>(referenceBase->getElement());
       std::dynamic_pointer_cast<ConcreteElement>(referenceBase) && x)
      transitiveIncludes.insert(x->getSchemaLocation());
  return transitiveIncludes;
}

/**
 * @fn findFirstTransitiveIncludedLocation
 * @param includedLocations Java: includedFiles
 * @param allLocations Java: parseElements
 * @oldcode (Java)
 *  for(String includedFile : includedFiles){
 *      parseElements.keySet()
 *              .stream()
 *              .filter(fileNameAux -> fileNameAux.endsWith(includedFile))
 *              .findFirst()
 * @note VERIFIED
 */
auto findFirstTransitiveIncludedLocation(
    const std::set<SchemaLocation>& includedLocations,
    const std::map<SchemaLocation, std::list<std::shared_ptr<ReferenceBase>>>& allLocations)
{
  for(auto& includedLocation : includedLocations)
    for(auto& pair : allLocations)
      if(pair.first == includedLocation)
        return pair.second;
  return std::list<std::shared_ptr<ReferenceBase>>{};
}


void XsdParserCore::resolveInnerRefs(void)
{
  std::map<SchemaLocation, bool> doneList;

  for(auto& element : m_parseElements)
    doneList.emplace(element.first, false);

  while(std::ranges::any_of(doneList, [](auto& pair) { return pair.second == false; }))
  {
    for(auto& pair : m_parseElements)
    {
      auto& fileLocation = pair.first;
      if (!doneList.at(fileLocation))
      {
        auto includedLocations = getIncludedLocations(pair.second);
        auto transitiveIncludes = getTransitiveIncludes(findFirstTransitiveIncludedLocation(includedLocations, m_parseElements));

        includedLocations.merge(transitiveIncludes);
        for(auto& schema : getResultXsdSchemas())
          if(std::ranges::any_of(schema->getChildren<XsdInclude>(),
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
          unsolvedReferenceList.remove_if([this](auto& u)
          { return std::ranges::any_of(m_parserUnsolvedElements,
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
            if(!m_parseElements.contains(includedFile))
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
 * @note VERIFIED
 */
void XsdParserCore::replaceUnsolvedReference(
    std::map<std::string, std::list<std::shared_ptr<NamedConcreteElement>>> concreteElementsMap,
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

    for (auto& concreteElement : concreteElements)
    {
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
 * @fn getUnsolvedInnerElement
 * @param unsolvedReference Java: unsolvedReference
 * @param unsolvedElements Java: parserUnsolvedElementsMap
 * @oldcode (Java)
 *  Optional<UnsolvedReferenceItem> innerEntry =
 *          parserUnsolvedElementsMap.stream()
 *                  .filter(unsolvedReferenceObj ->
 *                          unsolvedReferenceObj.getUnsolvedReference()
 *                                  .getRef()
 *                                  .equals(unsolvedReference.getRef()))
 *                  .findFirst();
 * @note VERIFIED
 */
auto getUnsolvedInnerElement(
    std::shared_ptr<UnsolvedReference> unsolvedReference,
    const std::list<std::shared_ptr<UnsolvedReferenceItem>>& unsolvedElements)
{
  for(auto& unsolvedReferenceObj : unsolvedElements)
    if(unsolvedReference->getRef() &&
       unsolvedReferenceObj->getUnsolvedReference()->getRef() == unsolvedReference->getRef())
      return unsolvedReferenceObj;
  return std::shared_ptr<UnsolvedReferenceItem>();
}

/**
 * Saves an occurrence of an element which couldn't be resolved in the {@link XsdParser#replaceUnsolvedReference}
 * method, which can be accessed at the end of the parsing process in order to verify if were there were any
 * references that couldn't be solved.
 * @param unsolvedReference The unsolved reference which couldn't be resolved.
 * @note VERIFIED
 */
void XsdParserCore::storeUnsolvedItem(
    std::shared_ptr<UnsolvedReference> unsolvedReference)
{
    if (m_parserUnsolvedElements.empty())
        m_parserUnsolvedElements.push_back(create<UnsolvedReferenceItem>(unsolvedReference));
    else
    {
      if(auto innerEntry = getUnsolvedInnerElement(unsolvedReference, m_parserUnsolvedElements); innerEntry)
        innerEntry->getParents().push_back(unsolvedReference->getParent());
      else
        m_parserUnsolvedElements.push_back(create<UnsolvedReferenceItem>(unsolvedReference));
    }
}



/**
 * Adds an {@link UnsolvedReference} object to the {@link XsdParser#unsolvedElements} list which should be solved
 * at a later time in the parsing process.
 * @param unsolvedReference The unsolvedReference to add to the unsolvedElements list.
 * @note VERIFIED
 */
void XsdParserCore::addUnsolvedReference(
    std::shared_ptr<UnsolvedReference> unsolvedReference)
{
  std::shared_ptr<XsdSchema> schema;
  try { schema = XsdAbstractElement::getXsdSchema(unsolvedReference->getElement(), {}); }
  catch(ParentAvailableException& e) { }

  // Note: refactored for ease of understanding
  if(schema)
    m_unsolvedElements[schema->getFileLocation()].push_back(unsolvedReference);
  else
    m_unsolvedElements[m_currentFile].push_back(unsolvedReference);
}


/**
 * Adds a new file to the parsing queue. This new file appears by having xsd:import or xsd:include tags in the
 * original file to parse.
 * @param schemaLocation A new file path of another XSD file to parse.
 */
void XsdParserCore::addLocationToParse(SchemaLocation schemaLocation)
{
  schemaLocation.setParentPaths(m_currentFile);
  m_schemaLocations.insert(schemaLocation);
  auto result = m_schemaLocationsMap.emplace(schemaLocation, m_currentFile);
  if(!result.second)
    assert(m_schemaLocationsMap.at(schemaLocation) == m_currentFile);
}
