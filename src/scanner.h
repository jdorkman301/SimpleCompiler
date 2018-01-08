#include <cstddef>
#include <iostream>
#include <fstream>
#include <string>
#include "filter.h"
#include "token.h"

using namespace std;

#ifndef SCANNER_H
#define SCANNER_H

const int IntNextChars = 23;
const int IntStates = 13;

enum nextChar {lessThanCaret, greaterThanCaret, equalSign, exclamationPoint, colon,
plusSign, minusSign, multiplicationSign, divisionSign, ampersand, percentSign,
period, comma, semicolon, openParenthesis, closeParenthesis, openBracket,
closeBracket, openSquareBracket, closeSquareBracket, letter, digit, ws};

enum states {state1, state2, state3, state4, state5, state6, state7, state8,
state9, state10, state11, state12, state13};

token getNextToken(ifstream &);

string tableReader(int, int);

token checkForKeyword(token);

token FADdriver(ifstream &);

#endif
