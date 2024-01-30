#pragma once
#include "Events.h"

struct BaseState;
struct StateClinicalDocument;


struct BaseState {
    using transitions = ctfsm::type_map<
        std::pair<ClinicalDocumentEnterEvent, StateClinicalDocument>
    >;
};

struct StateClinicalDocument {
    using transitions = ctfsm::type_map<
        std::pair<ClinicalDocumentEnterEvent, StateClinicalDocument>
    >;
};