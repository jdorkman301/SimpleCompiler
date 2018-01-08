#include <cstddef>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#ifndef FILTER_H
#define FILTER_H

struct filter
{
  string tokenString;
  char readChar;
  int numberOfLines;
  int numberOfColumns;
};

class Stack
{
private:
  char *p;
  int top;

public:
  Stack();
  ~Stack();

  void push(char elem);
  void pop();
  bool isEmpty();
};


filter getNextChar(filter, ifstream &, Stack &);

#endif
