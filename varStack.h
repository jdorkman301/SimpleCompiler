#ifndef VARSTACK_H
#define VARSTACK_H

#include <string>

using namespace std;

class varStack
{
private:
  string *varStackArray;
  int varStackSize;
  int top;

public:
  //Constructor
  varStack(int);

  //Destructor
  ~varStack();

  //Stack Operations
  void push(string);
  void pop(string &);
  int find(string);
  bool isFull();
  bool isEmpty();

};
#endif
