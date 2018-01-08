#include "token.h"
#include "testTree.h"
#include "varStack.h"
#include <iostream>
#include <fstream>

using namespace std;


token *head;
//head from extern token* head
//in token.h
bool inGlobalScope = true;
bool hasSemanticsError = false;
bool inVars = false;
bool tempStackInit = false;

varStack tempStack(100);

token* insertNode( token* newToken )
{
  token *newNode; //To be the new node in tree
  token *nodePtr; //To move through the tree
  //Allocate a new node and store the new node there
  newNode = new token;

  //if there are no nodes in the tree
  //make newNode the first node

  if (!head)
  {
    cout<<"creating headnode"<<endl;
    head = newNode;
    head->childSubtree1 = nullptr;
    head->childSubtree2 = nullptr;
    head->childSubtree3 = nullptr;
    head->childSubtree4 = nullptr;
    head->childSubtree5 = nullptr;
    head->childSubtree6 = nullptr;
    head->childSubtree7 = nullptr;
    head->label = "headNode";
    head->level = 0;
    head->instance = "headNode";
    head->tokenId = NULL_tk;
    head->lineNumber = 0;
  }
  else
  {
    cout<<"head exists: newNode"<<endl;
    newNode->label = newToken->label;
    newNode->instance = newToken->instance;
    newNode->tokenId = newToken->tokenId;
    newNode->lineNumber = newToken->lineNumber;
    newNode->level = newToken->level;
    newNode->childSubtree1 = nullptr;
    newNode->childSubtree2 = nullptr;
    newNode->childSubtree3 = nullptr;
    newNode->childSubtree4 = nullptr;
    newNode->childSubtree5 = nullptr;
    newNode->childSubtree6 = nullptr;
    newNode->childSubtree7 = nullptr;
    //initialize nodePtr to head of list to move through tree
    nodePtr = head;
    int insertSuccessful = 0;
    while(insertSuccessful == 0)
    {
      if(nodePtr->childSubtree1 == nullptr)
      {//insert newToken into childSubtree1
        insertSuccessful = 1;
        newToken->level++;
        nodePtr->childSubtree1 = newToken;
      } else if(nodePtr->childSubtree1 != nullptr)
      {
        nodePtr = nodePtr->childSubtree1;
      }
    }//end while

  }//end else

return head;
}//end function

void codeGen( token* node, int level, varStack* globalStack, varStack* localStack, ofstream &outputFile)
{
  if(tempStackInit == false)
  {
    for(int z = 0; z < 100; z++)
    {
      string newTemp = "T";
      newTemp += to_string(z);
      tempStack.push(newTemp);
    }
  tempStackInit = true;
  }
  level++;
  if((node == nullptr) || (hasSemanticsError == true))
  {
    return;
  }
  else
  {
    if(node->instance != "")
    {
      
    }
    else
    {
      
    }
    if(node->label == "Program")
    {
      codeGen(node->childSubtree1, level, globalStack, localStack, outputFile);
      codeGen(node->childSubtree2, level, globalStack, localStack, outputFile);
    }

    if(node->label == "Vars")
    {
      inVars = true;
      token* varChild2 = node->childSubtree2;
      if(varChild2 != nullptr)
      {
          if(inGlobalScope == true)
          {
            if(globalStack->find(varChild2->instance) == -1)
            {
              globalStack->push(varChild2->instance);
            }
            else
            {
              cout<<"Global Stack Error: "<<varChild2->instance<<" is already defined"<<endl;
              hasSemanticsError = true;
              return;
            }
          }
          else
          {
            if(localStack->find(varChild2->instance) == -1)
            {
              localStack->push(varChild2->instance);
              outputFile<<"PUSH"<<endl;
            }
            else
            {
              cout<<"Local Stack Error: "<<varChild2->instance<<" is already defined"<<endl;
              cout<<"Local Stack contents are "<<endl;
              while(localStack->isEmpty() == false)
              {
                string popValue;
                localStack->pop(popValue);
                cout<<popValue<<endl;
              }
              hasSemanticsError = true;
              return;
            }
          }
      }
      codeGen(node->childSubtree3, level, globalStack, localStack, outputFile);
    }

    if(node->label == "Mvars")
    {
      token* varChild2 = node->childSubtree2;
      if(varChild2 != nullptr)
      {
        if(inGlobalScope == true)
        {
          if(globalStack->find(varChild2->instance) == -1)
          {
            globalStack->push(varChild2->instance);
          }
          else
          {
            cout<<"Global Stack Error: "<<varChild2->instance<<" is already defined"<<endl;
            hasSemanticsError = true;
            return;
          }
        }
        else
        {
          if(localStack->find(varChild2->instance) == -1)
          {
            localStack->push(varChild2->instance);
            outputFile<<"PUSH"<<endl;
          }
          else
          {
            cout<<"Local Stack Error: "<<varChild2->instance<<" is already defined"<<endl;
            cout<<"Local Stack contents are "<<endl;
            while(localStack->isEmpty() == false)
            {
              string popValue;
              localStack->pop(popValue);
              cout<<popValue<<endl;
            }
            hasSemanticsError = true;
            return;
          }
        }
        codeGen(node->childSubtree3, level, globalStack, localStack, outputFile);
      }
    }

    if(node->label == "Stats")
    {
      inVars = false;
      codeGen(node->childSubtree1, level, globalStack, localStack, outputFile);
      codeGen(node->childSubtree2, level, globalStack, localStack, outputFile);
    }
    if(node->label == "Mstat")
    {
      codeGen(node->childSubtree1, level, globalStack, localStack, outputFile);
      codeGen(node->childSubtree2, level, globalStack, localStack, outputFile);
    }

    if(node->label == "Stat")
    {
        codeGen(node->childSubtree1, level, globalStack, localStack, outputFile);
        codeGen(node->childSubtree2, level, globalStack, localStack, outputFile);
        codeGen(node->childSubtree3, level, globalStack, localStack, outputFile);
        codeGen(node->childSubtree4, level, globalStack, localStack, outputFile);
        codeGen(node->childSubtree5, level, globalStack, localStack, outputFile);
        codeGen(node->childSubtree6, level, globalStack, localStack, outputFile);
    }

    if(node->label == "F")
    {
      token* varChild1 = node->childSubtree1;
      if(varChild1->label == "Open Paranthesis")
      {
        codeGen(node->childSubtree2, level, globalStack, localStack, outputFile);
        outputFile<<"MULT -1"<<endl;
      }
      else
      {
        codeGen(node->childSubtree1, level, globalStack, localStack, outputFile);
      }
    }

    if(node->label == "R")
    {
      token* childSubtree1 = node->childSubtree1;
      if(childSubtree1->label == "Open Bracket")
      {
        codeGen(node->childSubtree2, level, globalStack, localStack, outputFile);
      }
      else
      {
        if(childSubtree1->label == "Number")
        {
          outputFile<<"LOAD "<<childSubtree1->instance<<endl;
        }
        else
        {
          if(localStack->find(childSubtree1->instance) == -1)
          {
            if(globalStack->find(childSubtree1->instance) == -1)
            {
              cout<<"Error: "<<childSubtree1->instance<<" is not defined in this scope"<<endl;
              return;
            }
            else
            {
              outputFile<<"LOAD "<<childSubtree1->instance<<endl;
            }
          }
          else
          {
            string newTemp;
            tempStack.pop(newTemp);
            globalStack->push(newTemp);
            outputFile<<"LOAD "<<newTemp<<endl;
            outputFile<<"STACKR "<<localStack->find(childSubtree1->instance)<<endl;
          }
        }
      }
    }
    if(node->label == "Block")
    {
        inGlobalScope = false;
        inVars = false;
        codeGen(node->childSubtree1, level, globalStack, localStack, outputFile);
        codeGen(node->childSubtree2, level, globalStack, localStack, outputFile);
        codeGen(node->childSubtree3, level, globalStack, localStack, outputFile);
        codeGen(node->childSubtree4, level, globalStack, localStack, outputFile);
    }

    if(node->label == "Begin")
    {
      localStack->push("Begin");
    }

    if(node->label == "End")
    {
      string popValue;
      localStack->pop(popValue);
      if((popValue != "Begin") && (localStack->isEmpty() == false))
      {
        outputFile<<"POP"<<endl;
        localStack->pop(popValue);
      }
      while((popValue != "Begin") && (localStack->isEmpty() == false))
      {
        outputFile<<"POP"<<endl;
        localStack->pop(popValue);
      }
    }

    if(node->label == "In")
    {
      token* varChild = node->childSubtree2;
        if(localStack->find(varChild->instance) == -1)
        {
          if(globalStack->find(varChild->instance) == -1)
          {
            cout<<"Error: "<<varChild->instance<<" is not defined in this scope"<<endl;
          }
          else
          {
            outputFile<<"READ "<<varChild->instance<<endl;
          }
        }
        else
        {
          string newTemp;
          tempStack.pop(newTemp);
          outputFile<<"READ "<<newTemp<<endl;
          outputFile<<"LOAD "<<newTemp<<endl;
          outputFile<<"STACKW "<<localStack->find(varChild->instance)<<endl;
          globalStack->push(newTemp);
        }
    }

    if(node->label == "Out")
    {
      codeGen(node->childSubtree2, level, globalStack, localStack, outputFile);
      string newTemp;
      tempStack.pop(newTemp);
      globalStack->push(newTemp);
      outputFile<<"STORE "<<newTemp<<endl;
      outputFile<<"WRITE "<<newTemp<<endl;
    }

    if(node->label == "If")
    {
      codeGen(node->childSubtree5, level, globalStack, localStack, outputFile);
      string tempVar;
      tempStack.pop(tempVar);
      outputFile<<"STORE "<<tempVar<<endl;
      codeGen(node->childSubtree3, level, globalStack, localStack, outputFile);
      outputFile<<"SUB "<<tempVar<<endl;
			globalStack->push(tempVar);
      string label;
      tempStack.pop(label);
      token* varChild4 = node->childSubtree4;
			varChild4 = varChild4->childSubtree1;
      if(varChild4->instance == ">")
      {
        outputFile<<"BRZNEG "<<label<<endl;
      }
      else if(varChild4->instance == "<")
      {
        outputFile<<"BRZPOS "<<label<<endl;
      }
      else if(varChild4->instance == ">=")
      {
        outputFile<<"BRNEG "<<label<<endl;
      }
      else if(varChild4->instance == "<=")
      {
        outputFile<<"BRPOS "<<label<<endl;
      }
      else if(varChild4->instance == "==")
      {
        outputFile<<"BRZERO "<<label<<endl;
      }
      else if(varChild4->instance == "!=")
      {
        outputFile<<"BRNEG "<<label<<endl;
        outputFile<<"BRPOS "<<label<<endl;
      }
      codeGen(node->childSubtree7, level, globalStack, localStack, outputFile);
      outputFile<<label<<": NOOP"<<endl;
    }

    if(node->label == "Assign")
    {
      token* varChild1 = node->childSubtree1;
//      outputFile<<"LOAD "<<varChild1->instance;
      codeGen(node->childSubtree3, level, globalStack, localStack, outputFile);

      if(localStack->find(varChild1->instance) != -1)
      {
        string newTemp;
        tempStack.pop(newTemp);
        globalStack->push(newTemp);
        outputFile<<"LOAD "<<newTemp<<endl;
        outputFile<<"STACKW "<<localStack->find(varChild1->instance);
      }
      else if(globalStack->find(varChild1->instance) != -1)
      {
        outputFile<<"STORE "<<varChild1->instance<<endl;
      }
      else
      {
        cout<<"Error: "<<varChild1->instance<<" is undefined"<<endl;
        hasSemanticsError = true;
      }
    }

    if(node->label == "Loop")
    {
      codeGen(node->childSubtree5, level, globalStack, localStack, outputFile);
      string tempVar;
      tempStack.pop(tempVar);
      string labelUp;
      tempStack.pop(labelUp);
      outputFile<<labelUp<<": LOAD "<<tempVar<<endl;
      codeGen(node->childSubtree3, level, globalStack, localStack, outputFile);
      outputFile<<"SUB "<<tempVar<<endl;
	  globalStack->push(tempVar);
      string labelOut;
      tempStack.pop(labelOut);
      token* varChild4 = node->childSubtree4;
	  varChild4 = varChild4->childSubtree1;
      if(varChild4->label == "Greater Than")
      {
        outputFile<<"BRZNEG "<<labelOut<<endl;
      }
      else if(varChild4->label == "Less Than")
      {
        outputFile<<"BRZPOS "<<labelOut<<endl;
      }
      else if(varChild4->label == "Greater Than Equal")
      {
        outputFile<<"BRNEG "<<labelOut<<endl;
      }
      else if(varChild4->label == "Less Than Equal")
      {
        outputFile<<"BRPOS "<<labelOut<<endl;
      }
      else if(varChild4->label == "Equal Equal")
      {
        outputFile<<"BRZERO "<<labelOut<<endl;
      }
      else if(varChild4->label == "Not Equal")
      {
        outputFile<<"BRNEG "<<labelOut<<endl;
        outputFile<<"BRPOS "<<labelOut<<endl;
      }
      codeGen(node->childSubtree7, level, globalStack, localStack, outputFile);
      outputFile<<"BR "<<labelUp<<endl;
      outputFile<<labelOut<<": NOOP"<<endl;
    }

    if(node->label == "Number")
    {
      outputFile<<"LOAD "<<node->instance<<endl;
    }

    if(node->label == "Expr")
    {
      token* varChild2 = node->childSubtree2;
      if(varChild2 == nullptr)
      {
        codeGen(node->childSubtree1, level, globalStack, localStack, outputFile);
      }
      else
      {
        codeGen(node->childSubtree3, level, globalStack, localStack, outputFile);
        string newTemp;
        tempStack.pop(newTemp);
        globalStack->push(newTemp);
        outputFile<<"STORE "<<newTemp<<endl;
        codeGen(node->childSubtree1, level, globalStack, localStack, outputFile);
        if(varChild2->label == "Plus")
        {
          outputFile<<"ADD "<<newTemp<<endl;
        }
        else
        {
          outputFile<<"SUB "<<newTemp<<endl;
        }
      }
    }

    if(node->label == "M")
    {
      token* varChild2 = node->childSubtree2;
      if(varChild2 == nullptr)
      {
        codeGen(node->childSubtree1, level, globalStack, localStack, outputFile);
      }
      else
      {
        codeGen(node->childSubtree3, level, globalStack, localStack, outputFile);
        string newTemp;
        tempStack.pop(newTemp);
        globalStack->push(newTemp);
        outputFile<<"STORE "<<newTemp<<endl;
        codeGen(node->childSubtree1, level, globalStack, localStack, outputFile);
        if(varChild2->label == "Multiply")
        {
          outputFile<<"MULT "<<newTemp<<endl;
        }
        else
        {
          outputFile<<"DIV "<<newTemp<<endl;
        }
      }
    }

//    if(hasSemanticsError == false)
//      codeGen(node->childSubtree1, level, globalStack, localStack, outputFile);
//    if(hasSemanticsError == false)
//      codeGen(node->childSubtree2, level, globalStack, localStack, outputFile);
//    if(hasSemanticsError == false)
//      codeGen(node->childSubtree3, level, globalStack, localStack, outputFile);
//    if(hasSemanticsError == false)
//      codeGen(node->childSubtree4, level, globalStack, localStack, outputFile);
//    if(hasSemanticsError == false)
//      codeGen(node->childSubtree5, level, globalStack, localStack, outputFile);
//    if(hasSemanticsError == false)
//      codeGen(node->childSubtree6, level, globalStack, localStack, outputFile);
//    if(hasSemanticsError == false)
//      codeGen(node->childSubtree7, level, globalStack, localStack, outputFile);
  }
  return;
}//end function

token* getNode(string label)
{
  token* newNode;
  newNode = new token;

  newNode->label = label;
  newNode->instance = "";
  newNode->tokenId = NULL_tk;
  newNode->lineNumber = 0;
  newNode->level = 0;
  newNode->childSubtree1 = nullptr;
  newNode->childSubtree2 = nullptr;
  newNode->childSubtree3 = nullptr;
  newNode->childSubtree4 = nullptr;
  newNode->childSubtree5 = nullptr;
  newNode->childSubtree6 = nullptr;
  newNode->childSubtree7 = nullptr;

  return newNode;
}
