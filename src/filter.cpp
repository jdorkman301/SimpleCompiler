#include <iostream>
#include <fstream>
#include <string>
#include "filter.h"

using namespace std;

Stack::Stack()
{
  top=-1;
  p=new char[1];
}

Stack::~Stack()
{
  delete [] p;
}

void Stack::push(char elem)
{
  top++;
  p[top]=elem;
}

void Stack::pop()
{
  if(top != -1)
  {
    char ret=p[top];
    top--;
  }
}

bool Stack::isEmpty()
{
  if(top == -1)
  {
    return true;
  }
  else
  {
    return false;
  }
}

filter getNextChar(filter filterObject, ifstream &file, Stack &commentStack)
{
  while (!file.eof())
  {
    file.read(&filterObject.readChar, sizeof(filterObject.readChar));
    if(filterObject.readChar == '#')
    {
      if(commentStack.isEmpty())
      {
        commentStack.push(filterObject.readChar);
      }
      else
      {
        commentStack.pop();
        file.read(&filterObject.readChar, sizeof(filterObject.readChar));
        if(filterObject.readChar == '#')
        {
           commentStack.push(filterObject.readChar);
        }
      }
    }
    return filterObject;
  }
}
