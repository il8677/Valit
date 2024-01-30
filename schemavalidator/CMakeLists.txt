CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT(schemavalidator)

find_package(LibXml2 REQUIRED PATH ../vendor/libxml)

SET(SOURCES 
    main.cpp
    XMLEventGenerator.cpp
    XMLDoc.cpp
)

SET(HEADERS
    XMLEventGenerator.h
    XMLDoc.h
)


ADD_EXECUTABLE(schemavalidator ${SOURCES} ${HEADERS})
SET_PROPERTY(TARGET schemavalidator PROPERTY CXX_STANDARD 20)