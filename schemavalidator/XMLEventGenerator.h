#pragma once
#include <string>
#include <iostream>
#include <fsm.hpp>

#include "States.h"
#include "XMLDoc.h"

template<typename T>
class XMLEventGenerator{
public:
    void handle(XMLDoc& doc){
        // Handle the first node
        std::string currentNode = doc.getCurrentNode();
        handleNode(currentNode, doc);

        // Main loop
        while(!doc.isEmpty()){
            if(doc.nextIsAttribute()){
                auto [k, v] = doc.getCurrentAttribute();
                fsm(Attribute(k, v));
                doc.advanceAttribute();
            }else if(doc.nextIsChildNode()){
                doc.nodeDown();
                std::string currentNode = doc.getCurrentNode();
                handleNode(currentNode, doc);
            }else if(doc.nextIsSibling()){
                throw std::runtime_error("Not implemented");
            }else{
                throw std::runtime_error("Invalid doc state");
            }
        }
    }

private:
    void enterEvent(const std::string& str){
        if(str == "ClinicalDocument") fsm(ClinicalDocumentEnterEvent());
        else if(str == "realmCode") fsm(RealmCodeEnterEvent());
        else fsm(ErrorEvent());
    }

    void handleNode(std::string& nodeName, XMLDoc& doc){
        try{
            enterEvent(nodeName);
        }catch(std::runtime_error& err){
            std::cout << nodeName << ": " << err.what() << std::endl;
            doc.errorOut();
        }
    }

    ctfsm::fsm<T> fsm;
};

