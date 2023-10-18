#include "XsdParserCore.h"

#include <algorithm>

#include <xsdelements/XsdElement.h>
#include <xsdelements/XsdSchema.h>
#include <xsdelements/XsdImport.h>
#include <xsdelements/elementswrapper/UnsolvedReference.h>



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
      if(auto e = std::dynamic_pointer_cast<XsdSchema>(element); e)
        rval.push_back(e);
  return rval;
}

std::string getSubStringAfter(std::string input, const char target)
{
  if(input.contains(target))
    return input.substr(input.find_last_of(target) + 1);
  return input;
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

    auto path = getSubStringAfter(schema->getFilePath(), '/');
    for(auto e : schema->getNamespaces())
      schema->resolveNameSpace(e.first, path);
  }

  for(auto& pair : m_parseElements)
  {
    std::shared_ptr<XsdSchema> xsdSchema = findXsdSchema(pair.second);

    std::map<std::string, NamespaceInfo> ns = xsdSchema->getNamespaces();

    std::list<std::shared_ptr<UnsolvedReference>> unsolvedReferenceList;
    if(m_unsolvedElements.contains(pair.first))
      for(auto& unsolvedElement : m_unsolvedElements.at(pair.first))
        if(unsolvedElement->getRef().contains(':'))
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
          NamespaceInfo namespaceInfo = ns.at(unsolvedElementNamespace);
          std::list<std::shared_ptr<ReferenceBase>> importedElements;
          auto unsolvedElementSchema = unsolvedReference->getElement()->getXsdSchema();

          if (unsolvedElementSchema &&
              unsolvedElementSchema->getTargetNamespace() &&
              unsolvedElementSchema->getTargetNamespace() == namespaceInfo.getName())
            importedElements = unsolvedElementSchema->getElements();
          else
          {
            auto importedFileLocation = ns.at(unsolvedElementNamespace).getFile();
            assert(importedFileLocation);

            std::string importedFileName = importedFileLocation.value();

            std::string finalImportedFileName = importedFileName;
            if(m_parseElements.contains(finalImportedFileName))
              importedElements = m_parseElements.at(finalImportedFileName);
          }

          std::map<std::string, std::list<std::shared_ptr<NamedConcreteElement>>> concreteElementsMap;
          for(auto& concreteElement : importedElements)
            if(auto x = std::dynamic_pointer_cast<NamedConcreteElement>(concreteElement); x)
              concreteElementsMap[x->getName()].push_back(x);
          replaceUnsolvedImportedReference(concreteElementsMap, unsolvedReference, pair.first);
        }
      }

      unsolvedReferenceList.clear();
      if(m_unsolvedElements.contains(pair.first))
        for(auto& unsolvedElement : m_unsolvedElements.at(pair.first))
          if(unsolvedElement->getRef().contains(':'))
            unsolvedReferenceList.push_back(unsolvedElement);

      currentUnsolvedReferenceListSize = unsolvedReferenceList.size();
    } while (currentUnsolvedReferenceListSize != startingUnsolvedReferenceListSize);
  }
}


void XsdParserCore::replaceUnsolvedImportedReference(std::map<std::string, std::list<std::shared_ptr<NamedConcreteElement>>> concreteElementsMap,
                                                     std::shared_ptr<UnsolvedReference> unsolvedReference,
                                                     std::string fileName)
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

        m_unsolvedElements.at(fileName).remove(unsolvedReference);
    }
}



void XsdParserCore::resolveInnerRefs(void)
{
    Arraystd::list<bool> doneList;
    Arraystd::list<std::string> fileNameList = new Arraystd::list<>(parseElements.keySet());

    for (int i = 0; i < fileNameList.size(); i++) {
        doneList.add(false);
    }

    while (doneList.contains(bool.FALSE)){
        for (int i = 0; i < fileNameList.size(); i++) {
            std::string fileName = fileNameList.get(i);

            if (!doneList.get(i)){
                std::list<std::string> includedFiles =
                        parseElements.get(fileName)
                                .stream()
                                .filter(referenceBase -> referenceBase instanceof ConcreteElement && referenceBase.getElement() instanceof XsdInclude)
                                .map(referenceBase -> (((XsdInclude) referenceBase.getElement()).getSchemaLocation()))
                                ;

                Set<std::string> transitiveIncludes = new HashSet<>();

                for(std::string includedFile : includedFiles){
                    parseElements.keySet()
                            .stream()
                            .filter(fileNameAux -> fileNameAux.endsWith(includedFile))
                            .findFirst()
                            .ifPresent(fullIncludedFileName -> transitiveIncludes.addAll(parseElements.get(fullIncludedFileName)
                            .stream()
                            .filter(referenceBase -> referenceBase instanceof ConcreteElement && referenceBase.getElement() instanceof XsdInclude)
                            .map(referenceBase -> (((XsdInclude) referenceBase.getElement()).getSchemaLocation()))
                            ));
                }

                includedFiles.addAll((transitiveIncludes));
                includedFiles.addAll(getResultXsdSchemas().filter(schema -> schema.getChildrenIncludes().anyMatch(xsdInclude -> xsdInclude.getSchemaLocation().equals(fileName))).map(XsdSchema::getFilePath).distinct());
                includedFiles = includedFiles.stream().distinct();

                std::list<std::shared_ptr<ReferenceBase>> includedElements = new Arraystd::list<>(parseElements.get(fileName));

                includedFiles.stream().filter(Objects::nonNull).forEach(includedFile ->{
                    std::string includedFilename = includedFile.substring(includedFile.lastIndexOf("/")+1);

                    includedElements.addAll(parseElements.getOrDefault(includedFile, parseElements.get(parseElements.keySet().stream().filter(k -> k.endsWith(includedFilename)).findFirst().get())));
                });

                std::map<std::string, std::list<std::shared_ptr<NamedConcreteElement>>> concreteElementsMap =
                        includedElements.stream()
                                .filter(concreteElement -> concreteElement instanceof NamedConcreteElement)
                                .map(concreteElement -> (NamedConcreteElement) concreteElement)
                                .collect(groupingBy(NamedConcreteElement::getName));

                std::list<std::shared_ptr<UnsolvedReference>> unsolvedReferenceList = m_unsolvedElements.getOrDefault(fileName, new Arraystd::list<>())
                        .stream()
                        .filter(unsolvedElement -> !unsolvedElement.getRef().contains(":"))
                        ;

                long startingUnsolvedReferenceListSize = unsolvedReferenceList.size();
                long currentUnsolvedReferenceListSize = 0;
                bool solveMore = true;
                bool doneSomething = false;

                do {
                    unsolvedReferenceList = unsolvedReferenceList.stream().filter(u -> parserUnsolvedElementsMap.stream().noneMatch(u1 -> u == u1.getUnsolvedReference()));

                    for (auto unsolvedReference : unsolvedReferenceList) {
                        doneSomething = true;

                        replaceUnsolvedReference(concreteElementsMap, unsolvedReference, fileName);
                    }

                    unsolvedReferenceList = m_unsolvedElements.getOrDefault(fileName, new Arraystd::list<>())
                            .stream()
                            .filter(unsolvedElement -> !unsolvedElement.getRef().contains(":"))
                            ;

                    currentUnsolvedReferenceListSize = unsolvedReferenceList.size();

                    if (currentUnsolvedReferenceListSize == startingUnsolvedReferenceListSize){
                        solveMore = false;
                    }

                    startingUnsolvedReferenceListSize = currentUnsolvedReferenceListSize;
                } while(solveMore);

                doneList.set(i, true);

                if (doneSomething){
                    for(std::string includedFile: includedFiles){
                        int idx = fileNameList.indexOf(includedFile);

                        if (idx != -1){
                            doneList.set(idx, false);
                        }
                    }
                }
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
                                             std::shared_ptr<UnsolvedReference> unsolvedReference, std::string fileName)
{
    std::list<std::shared_ptr<NamedConcreteElement>> concreteElements = concreteElementsMap.get(unsolvedReference->getRef());

    if (concreteElements != null){
        StringMap oldElementAttributes = new std::unordered_map<>(unsolvedReference.getElement().getAttributesMap());

        for (NamedConcreteElement concreteElement : concreteElements) {
            NamedConcreteElement substitutionElementWrapper;

            if (!unsolvedReference.isTypeRef()){
                XsdNamedElements substitutionElement = (XsdNamedElements) concreteElement.getElement().clone(oldElementAttributes, concreteElement.getElement().getParent());

                substitutionElementWrapper = (NamedConcreteElement) ReferenceBase::createFromXsd(substitutionElement);
            } else {
                substitutionElementWrapper = concreteElement;
            }

            unsolvedReference.getParent().replaceUnsolvedElements(substitutionElementWrapper);
        }

        m_unsolvedElements.get(fileName).remove(unsolvedReference);
    } else {
        storeUnsolvedItem(unsolvedReference);
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
        if(unsolvedReferenceObj->getUnsolvedReference()->getRef() == unsolvedReference->getRef())
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
    catch(ParentAvailableException e) { }

    std::string localCurrentFile = m_currentFile;

    if(schema)
      localCurrentFile = schema->getFilePath();

    std::list<std::shared_ptr<UnsolvedReference>> unsolved;
    if(m_unsolvedElements.contains(localCurrentFile))
      unsolved = m_unsolvedElements.at(localCurrentFile);

    unsolved.push_back(unsolvedReference);
}


/**
 * Adds a new file to the parsing queue. This new file appears by having xsd:import or xsd:include tags in the
 * original file to parse.
 * @param schemaLocation A new file path of another XSD file to parse.
 */
void XsdParserCore::addFileToParse(std::string schemaLocation)
{
  std::string fullSchemaLocation = m_currentFile.substring(0, m_currentFile.lastIndexOf('/') + 1) + schemaLocation;
  bool urlSchemaLoction = false;

  if (!m_schemaLocations.contains((urlSchemaLoction = schemaLocation.startsWith("http")) ? schemaLocation
      : (fullSchemaLocation = cleanPath(fullSchemaLocation))) && schemaLocation.endsWith(".xsd")) {
    if (urlSchemaLoction) {
      m_schemaLocations.add(schemaLocation);
      m_schemaLocationsMap.put(schemaLocation, m_currentFile);
    } else {
      m_schemaLocations.add(fullSchemaLocation);
      m_schemaLocationsMap.put(fullSchemaLocation, m_currentFile);
    }
  }
}
