//
// Created by Мороз Максим on 06/10/2019.
//

#ifndef CPP_YELLOW_BELT_TOKEN_H
#define CPP_YELLOW_BELT_TOKEN_H

#pragma once

#include <sstream>
#include <vector>
using namespace std;

enum class TokenType {
    DATE,
    EVENT,
    COLUMN,
    LOGICAL_OP,
    COMPARE_OP,
    PAREN_LEFT,
    PAREN_RIGHT,
};

struct Token {
    const string value;
    const TokenType type;
};

vector<Token> Tokenize(istream& cl);

#endif //CPP_YELLOW_BELT_TOKEN_H
