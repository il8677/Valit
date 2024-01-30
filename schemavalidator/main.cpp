#include <iostream>
#include <fsm.hpp>
#include "XMLEventGenerator.h"
#include "XMLDoc.h"
#include "States.h"


int main(int argc, char* argv[]) {
    XMLDoc xmlDoc(argv[1]);
    XMLEventGenerator<BaseState> xml;
    xml.handle(xmlDoc);

    return 0;
}
