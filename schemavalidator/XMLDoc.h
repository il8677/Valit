#pragma once
#include <rapidxml.hpp>
#include <rapidxml_utils.hpp>
#include <string>
#include <stack>

class XMLDoc {
public:
    XMLDoc(const std::string& filePath);

    bool nextIsAttribute();
    bool nextIsChildNode();
    bool nextIsSibling();
    bool isEmpty();

    std::pair<std::string, std::string> nextNodeName() const;
    std::string getCurrentNode() const;
    
    void advanceAttribute();
    void nodeDown();
    void nodeNext();
    void nodeUp();

    void errorOut();

private:
    const rapidxml::xml_node<>* current() const { return nodes.top(); }
    rapidxml::xml_node<>* current() { return nodes.top(); }

    rapidxml::file<> xmlFile;
    rapidxml::xml_document<> doc;
    std::stack<rapidxml::xml_node<>*> nodes;
    rapidxml::xml_attribute<>* currentAttribute;
};