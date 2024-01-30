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
    }

private:
    void enterEvent(const std::string& str){
        if(str == "ClinicalDocument") fsm(ClinicalDocumentEnterEvent());
        else fsm(ErrorEvent());
    }

    void handleNode(std::string& nodeName, XMLDoc& doc){
        try{
            enterEvent(nodeName);
        }catch(std::runtime_error& err){
            std::cout << err.what() << std::endl;
            std::cout << "Error: Unexpected node " << nodeName << "\n";
            doc.errorOut();
        }
    }

    ctfsm::fsm<T> fsm;
};

