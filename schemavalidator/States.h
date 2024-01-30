#pragma once
#include "Events.h"
#include <exception>

struct BaseState;
struct StateClinicalDocument;
struct StateRealmCode;

struct BaseState {
    using transitions = ctfsm::type_map<
        std::pair<ClinicalDocumentEnterEvent, StateClinicalDocument>
    >;
};

// <ClinicalDocument>
struct StateClinicalDocument {
    using transitions = ctfsm::type_map<
        std::pair<RealmCodeEnterEvent, StateRealmCode>,
        std::pair<Attribute, StateClinicalDocument>
    >;
};

// <realmCode>
struct StateRealmCode {
    using transitions = ctfsm::type_map<
        std::pair<Attribute, StateRealmCode>
    >;

    void on_enter(Attribute& event){
        if(event.key == "code"){
            if(event.value != "AT")
                 throw std::runtime_error("Expected code to be AT");
        }
    }
};