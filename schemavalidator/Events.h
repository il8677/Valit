#pragma once
#include <string>

// General events
struct ErrorEvent {};
struct Attribute { 
    std::string key, value;
    Attribute(std::string _key, std::string _value) 
     : key(_key), value(_value){} 
};

// Node transitions
struct ClinicalDocumentEnterEvent {};
struct RealmCodeEnterEvent {};