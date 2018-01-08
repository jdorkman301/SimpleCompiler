#include <iostream>
#include "varStack.h"

using namespace std;

//Conbstructor
varStack::varStack(int size)
{
  varStackArray = new string[size];
  varStackSize = size;
  top = -1;
}

//Destructor
varStack::~varStack()
{
  delete [] varStackArray;
}

//push to stack, stack overflow if exceeds varStackSize
void varStack::push(string var)
{
  if(isFull())
  {
    cout<<"Stack Overflow: Exceeded "<<varStackSize<<" item limit"<<endl;
  }
  else
  {
    top++;
    varStackArray[top] = var;
  }
}

//pop stack, error if stack empty
void varStack::pop(string &var)
{
  if(isEmpty())
  {
    cout<<"Stack is empty: cannot pop"<<endl;
  }
  else
  {
    var = varStackArray[top];
    top--;
  }
}

bool varStack::isFull()
{
  bool status;

  if(top == varStackSize - 1)
  {
    status = true;
  }
  else
  {
    status = false;
  }

  return status;
}

bool varStack::isEmpty()
{
  bool status;

  if(top == -1)
  {
    status = true;
  }
  else
  {
    status = false;
  }

  return status;
}

//finds the var on the stack and returns the position of the var
//from TOS, else returns -1
int varStack::find(string var)
{
  int distanceFromTOS = 0;
  for(int i = top; i >= 0; i--)
  {
    if(varStackArray[i] == var)
    {
      return distanceFromTOS;
    }
    else
    {
      if(varStackArray[i] != "Begin")
      {
        distanceFromTOS++;
      }
      else
      {
        return -1;
      }
    }
  }
  return -1;
}
