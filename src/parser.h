#include <cstddef>
#include <iostream>
#include <fstream>
#include <string>
#include "token.h"

using namespace std;

#ifndef PARSER_H
#define PARSER_H

token setLineNumber(token &);

token* parser(ifstream &);

token* Program(ifstream &);
token* Vars(ifstream &);
token* Block(ifstream &);
token* Mvars(ifstream &);
token* Stats(ifstream &);
token* Stat(ifstream &);
token* Mstat(ifstream &);
token* In(ifstream &);
token* Out(ifstream &);
token* If(ifstream &);
token* Loop(ifstream &);
token* Assign(ifstream &);
token* Expr(ifstream &);
token* M(ifstream &);
token* F(ifstream &);
token* R(ifstream &);
token* RO(ifstream &);

#endif
