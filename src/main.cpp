//P1 submission by Jesse Schuff
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <cstring>
#include "parser.h"
#include "token.h"
#include "testTree.h"
#include "varStack.h"

using namespace std;

ofstream outAsm;

int main( int argc, char * argv[] )
{
  outAsm.open("out.asm");
  //read from file
  if (argc == 2)
  {

    ifstream inputFile;

    //token *head;
    const int filenameArraySize = 30;
    char filename[filenameArraySize];
    char * filePtr = filename;
    int checkFileSize = 0;
    filePtr = argv[1];
    for(int i = 0;; i++)
    {
      char charHolder;
      charHolder = filePtr[i];
      if(charHolder == '\0')
      {
        checkFileSize = i;
        break;
      }
    }
    if(checkFileSize > filenameArraySize)
    {
      cout<<"filename is too large. Keep filename under "<<filenameArraySize<<" characters long"<<endl;
      return 1;
    }
    int fileNameSize = 0;

    for(int i = 0; i < filenameArraySize; i++)
    {

      char charHolder;
      charHolder = filePtr[i];

      if(charHolder == '\0')
      {
        fileNameSize = i;
        filePtr[i] = '.';
        filePtr[i+1] = 'f';
        filePtr[i+2] = 's';
        filePtr[i+3] = '1';
        filePtr[i+4] = '7';
        filePtr[i+5] = '\0';
        break;

      }//end if

    }//end for loop
    fstream outputFile;
    outputFile.open(argv[1]);
    outputFile.seekg(0, outputFile.end);
    outputFile.seekg(-1, outputFile.cur);
    //outputFile.seekg(-1, outputFile.cur);
    //outputFile.seekg(0, -1);
    char checkForSpace;
    outputFile.read(&checkForSpace, sizeof(checkForSpace));
    if(checkForSpace == char(32))
    {
      //check for space char which is char(32)
      //if found, do nothing. if not found, go to
      //else and add the space
    } else {
      outputFile << " ";
    }
    //outputFile << " ";
    outputFile.close();
    inputFile.open(argv[1]);
    inputFile.seekg(0, inputFile.end);
    if(inputFile.fail())
    {
      cout<< argv[1] <<" does not exist -- program aborted."<<endl;
      return 1;
    }
    else if(inputFile.tellg() == 0)
    {
      cout<< argv[1] <<" is empty -- program aborted."<<endl;
      return 1;
    }
    else
    {
      inputFile.seekg(0, inputFile.beg);
      head = parser(inputFile);
      if(head->instance != "error")
      {
        varStack globalStack(100);
        varStack localStack(100);
        varStack *globalStackPtr = &globalStack;
        varStack *localStackPtr = &localStack;
        codeGen(head, 0, globalStackPtr, localStackPtr, outAsm);
        outAsm<<"\nSTOP"<<endl;
			  while(globalStack.isEmpty() == false)
        {
          string popValue;
          globalStack.pop(popValue);
          outAsm<<popValue<<" 0"<<endl;
        }
        outAsm.close();
      }
    }//end else
}//end argc == 2 if

if(argc == 1)
{
  string userInput;
  ofstream outputFile;
  ifstream inputFile;
  outputFile.open("keyboardRedirectFile", ios::app);
  while(getline(cin, userInput))
  {
    outputFile << userInput << endl;
  }//end while
  outputFile.close();

  inputFile.open("keyboardRedirectFile");
  inputFile.seekg(0, inputFile.end);
  if(inputFile.fail())
  {

    cout<< "keyboardRedirectFile does not exist -- program aborted."<<endl;
    inputFile.close();
    return 1;
  }
  else if(inputFile.tellg() == 0)
  {
    cout<<"keyboardRedirectFile is empty -- program aborted."<<endl;
    inputFile.close();
    return 1;
  }
  else
  {
    inputFile.seekg(0, inputFile.beg);
    head = parser(inputFile);
    if(head->instance != "error")
    {
      varStack globalStack(100);
      varStack localStack(100);
      varStack *globalStackPtr = &globalStack;
      varStack *localStackPtr = &localStack;
      codeGen(head, 0, globalStackPtr, localStackPtr, outAsm);
      outAsm<<"\nSTOP"<<endl;
			while(globalStack.isEmpty() == false)
      {
        string popValue;
        globalStack.pop(popValue);
        outAsm<<popValue<<" 0"<<endl;
      }
      outAsm.close();
    }
  }
remove("keyboardRedirectFile");

}//end argc == 1 if
  return 0;
}
