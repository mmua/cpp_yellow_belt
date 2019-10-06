//
// Created by Мороз Максим on 06/10/2019.
//

#ifndef CPP_YELLOW_BELT_CONDITION_PARSER_H
#define CPP_YELLOW_BELT_CONDITION_PARSER_H

#pragma once

#include "node.h"

#include <memory>
#include <iostream>

using namespace std;



enum class LogicalOperation {
    Or,
    And,
    Not
};

shared_ptr<Node> ParseCondition(istream& is);

void TestParseCondition();

#endif //CPP_YELLOW_BELT_CONDITION_PARSER_H
