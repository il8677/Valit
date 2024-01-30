#include <iostream>
#include <fsm.hpp>
#include "XMLEventGenerator.h"
#include "XMLDoc.h"
#include "States.h"
#include "ParseLineException.h"


int main(int argc, char* argv[]) {
    XMLDoc xmlDoc(argv[1]);
    XMLEventGenerator<BaseState> xml;

    try{
        xml.handle(xmlDoc);
    } catch (ParseLineException& e){
        e.print();
    }

    return 0;
}
