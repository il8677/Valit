#include "XMLDoc.h"
#include "ParseLineException.h"

unsigned int getLineNumber(char* start, char* end, char*& outLine){
    assert(start);
    assert(end);
    unsigned int linenum = 1;
    char* startLine;
    for(char* p = start; p <= end; p++)
    {
        if(*p == '\n') { 
            linenum++;
            startLine = strdup(p+1);
        }
    }

    outLine = startLine;

    return linenum;
}


XMLDoc::XMLDoc (const std::string& filePath) : xmlFile(filePath.c_str()){
    const int parseFlags = rapidxml::parse_validate_closing_tags;
    try{
        doc.parse<parseFlags>(xmlFile.data());
    }
    catch (const rapidxml::parse_error& e) {
        char* l;
        unsigned int errorLine = getLineNumber(xmlFile.data(), e.where<char>(), l);

        std::string errorMessage(e.what());
        throw ParseLineException(std::move(errorMessage), errorLine, l);
    }
    catch (const std::exception& e) {
        std::cerr << "Error was: " << e.what() << std::endl;
        return;
    }

    rapidxml::xml_node<>* node = doc.first_node();

    // Make sure theres one root node
    if(node->next_sibling() != nullptr){
        char* l;
        unsigned int errorLine = getLineNumber(xmlFile.data(), node->next_sibling()->name(), l);
        throw ParseLineException("More than one root node", errorLine, l);
    }
    
    nodes.push(node);
    currentAttribute = node->first_attribute();
}

bool XMLDoc::nextIsAttribute(){
    return currentAttribute;
}

bool XMLDoc::nextIsChildNode(){
    return current()->first_node();
}

bool XMLDoc::nextIsSibling(){
    return current()->next_sibling();
}

bool XMLDoc::isEmpty(){
    return nodes.size();
}

std::pair<std::string, std::string> XMLDoc::nextNodeName() const {
    std::string key(currentAttribute->name());
    std::string value(currentAttribute->value());

    return std::make_pair<>(key, value);
}

std::string XMLDoc::getCurrentNode() const {
    return current()->name();
}

void XMLDoc::advanceAttribute(){
    currentAttribute = currentAttribute->next_attribute();
}

void XMLDoc::nodeDown(){
    nodes.push(current()->first_node());
}

void XMLDoc::nodeNext(){
    auto node = nodes.top();
    nodes.pop();
    nodes.push(node->next_sibling());
}

void XMLDoc::nodeUp(){
    nodes.pop();
}

void XMLDoc::errorOut(){

    char* l;
    unsigned int errorLine = getLineNumber(xmlFile.data(), nodes.top()->next_sibling()->name(), l);
    throw ParseLineException("Line error:", errorLine, l);
}
