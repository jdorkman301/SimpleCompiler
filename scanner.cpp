#include <iostream>
#include <fstream>
#include <string>
#include "scanner.h"
#include "filter.h"
#include "token.h"

using namespace std;

string tokenNamesScanner[] = {"Identifier", "Number", "Keyword", "Operator", "EndOfFile"};

string table[IntStates][IntNextChars] =
{
  {"state2", "state3", "state6", "state8", "FINAL :TK", "FINAL +TK", "FINAL -TK",
  "FINAL *TK", "FINAL /TK", "FINAL &TK", "FINAL %TK", "state10", "FINAL ,TK",
  "FINAL ;TK", "FINAL (TK", "FINAL )TK", "FINAL {TK", "FINAL }TK", "FINAL [TK",
  "FINAL ]TK", "state11", "state12", "state1"},//end state1
  {"FINAL <TK", "FINAL <TK", "state4", "FINAL <TK", "FINAL <TK", "FINAL <TK",
  "FINAL <TK", "FINAL <TK", "FINAL <TK", "FINAL <TK", "FINAL <TK", "FINAL <TK",
  "FINAL <TK", "FINAL <TK", "FINAL <TK", "FINAL <TK", "FINAL <TK", "FINAL <TK",
  "FINAL <TK", "FINAL <TK", "FINAL <TK", "FINAL <TK", "FINAL <TK"},//end state2
  {"FINAL >TK", "FINAL >TK", "state5", "FINAL >TK", "FINAL >TK", "FINAL >TK",
  "FINAL >TK", "FINAL >TK", "FINAL >TK", "FINAL >TK", "FINAL >TK", "FINAL >TK",
  "FINAL >TK", "FINAL >TK", "FINAL >TK", "FINAL >TK", "FINAL >TK", "FINAL >TK",
  "FINAL >TK", "FINAL >TK", "FINAL >TK", "FINAL >TK", "FINAL >TK"},//end state3
  {"FINAL <=TK", "FINAL <=TK", "FINAL <=TK", "FINAL <=TK", "FINAL <=TK",
  "FINAL <=TK", "FINAL <=TK", "FINAL <=TK", "FINAL <=TK", "FINAL <=TK",
  "FINAL <=TK", "FINAL <=TK", "FINAL <=TK", "FINAL <=TK", "FINAL <=TK",
  "FINAL <=TK", "FINAL <=TK", "FINAL <=TK", "FINAL <=TK", "FINAL <=TK",
  "FINAL <=TK", "FINAL <=TK", "FINAL <=TK"},//end state4
  {"FINAL >=TK", "FINAL >=TK", "FINAL >=TK", "FINAL >=TK", "FINAL >=TK",
  "FINAL >=TK", "FINAL >=TK", "FINAL >=TK", "FINAL >=TK", "FINAL >=TK",
  "FINAL >=TK", "FINAL >=TK", "FINAL >=TK", "FINAL >=TK", "FINAL >=TK",
  "FINAL >=TK", "FINAL >=TK", "FINAL >=TK", "FINAL >=TK", "FINAL >=TK",
  "FINAL >=TK", "FINAL >=TK", "FINAL >=TK"},//end state5
  {"FINAL =TK", "FINAL =TK", "state7", "FINAL =TK", "FINAL =TK",
  "FINAL =TK", "FINAL =TK", "FINAL =TK", "FINAL =TK", "FINAL =TK",
  "FINAL =TK", "FINAL =TK", "FINAL =TK", "FINAL =TK", "FINAL =TK",
  "FINAL =TK", "FINAL =TK", "FINAL =TK", "FINAL =TK", "FINAL =TK",
  "FINAL =TK", "FINAL =TK", "FINAL =TK"},//end state6
  {"FINAL ==TK", "FINAL ==TK", "FINAL ==TK", "FINAL ==TK", "FINAL ==TK",
  "FINAL ==TK", "FINAL ==TK", "FINAL ==TK", "FINAL ==TK", "FINAL ==TK",
  "FINAL ==TK", "FINAL ==TK", "FINAL ==TK", "FINAL ==TK", "FINAL ==TK",
  "FINAL ==TK", "FINAL ==TK", "FINAL ==TK", "FINAL ==TK", "FINAL ==TK",
  "FINAL ==TK", "FINAL ==TK", "FINAL ==TK"},//end state7
  {"ERROR !TK", "ERROR !TK", "state9", "ERROR !TK", "ERROR !TK",
  "ERROR !TK", "ERROR !TK", "ERROR !TK", "ERROR !TK", "ERROR !TK",
  "ERROR !TK", "ERROR !TK", "ERROR !TK", "ERROR !TK", "ERROR !TK",
  "ERROR !TK", "ERROR !TK", "ERROR !TK", "ERROR !TK", "ERROR !TK",
  "ERROR !TK", "ERROR !TK", "ERROR !TK"},//end state8
  {"FINAL !=TK", "FINAL !=TK", "FINAL !=TK", "FINAL !=TK", "FINAL !=TK",
  "FINAL !=TK", "FINAL !=TK", "FINAL !=TK", "FINAL !=TK", "FINAL !=TK",
  "FINAL !=TK", "FINAL !=TK", "FINAL !=TK", "FINAL !=TK", "FINAL !=TK",
  "FINAL !=TK", "FINAL !=TK", "FINAL !=TK", "FINAL !=TK", "FINAL !=TK",
  "FINAL !=TK", "FINAL !=TK", "FINAL !=TK"},//end state9
  {"FINAL .TK", "FINAL .TK", "FINAL .TK", "FINAL .TK", "FINAL .TK",
  "FINAL .TK", "FINAL .TK", "FINAL .TK", "FINAL .TK", "FINAL .TK",
  "FINAL .TK", "FINAL .TK", "FINAL .TK", "FINAL .TK", "FINAL .TK",
  "FINAL .TK", "FINAL .TK", "FINAL .TK", "FINAL .TK", "FINAL .TK", "FINAL .TK",
  "state12", "FINAL .TK"},//end state10
  {"FINAL IDTK", "FINAL IDTK", "FINAL IDTK", "FINAL IDTK", "FINAL IDTK",
  "FINAL IDTK", "FINAL IDTK", "FINAL IDTK", "FINAL IDTK", "FINAL IDTK",
  "FINAL IDTK", "FINAL IDTK", "FINAL IDTK", "FINAL IDTK", "FINAL IDTK",
  "FINAL IDTK", "FINAL IDTK", "FINAL IDTK", "FINAL IDTK", "FINAL IDTK", "state11",
  "state11", "FINAL IDTK"},//end state11
  {"FINAL #TK", "FINAL #TK", "FINAL #TK", "FINAL #TK", "FINAL #TK",
  "FINAL #TK", "FINAL #TK", "FINAL #TK", "FINAL #TK", "FINAL #TK",
  "FINAL #TK", "state12", "FINAL #TK", "FINAL #TK", "FINAL #TK",
  "FINAL #TK", "FINAL #TK", "FINAL #TK", "FINAL #TK", "FINAL #TK", "FINAL #TK",
  "state12", "FINAL #TK"},//end state12
  {"FINAL #TK", "FINAL #TK", "FINAL #TK", "FINAL #TK", "FINAL #TK",
  "FINAL #TK", "FINAL #TK", "FINAL #TK", "FINAL #TK", "FINAL #TK",
  "FINAL #TK", "FINAL #TK", "FINAL #TK", "FINAL #TK", "FINAL #TK",
  "FINAL #TK", "FINAL #TK", "FINAL #TK", "FINAL #TK", "FINAL #TK", "FINAL #TK",
  "state12", "FINAL #TK"}//end state13
};

string tableReader(int state, int nextChar)
{
  string nextState = table[state][nextChar];
  return nextState;
}

token checkForKeyword(token tokenToCheck)
{
  if(tokenToCheck.instance == "Begin")
  {
     tokenToCheck.tokenId = KW_tk;
  }
  else if(tokenToCheck.instance == "End")
  {
     tokenToCheck.tokenId = KW_tk;
  }
  else if(tokenToCheck.instance == "Check")
  {
     tokenToCheck.tokenId = KW_tk;
  }
  else if(tokenToCheck.instance == "Loop")
  {
     tokenToCheck.tokenId = KW_tk;
  }
  else if(tokenToCheck.instance == "Void")
  {
     tokenToCheck.tokenId = KW_tk;
  }
  else if(tokenToCheck.instance == "Var")
  {
     tokenToCheck.tokenId = KW_tk;
  }
  else if(tokenToCheck.instance == "Return")
  {
     tokenToCheck.tokenId = KW_tk;
  }
  else if(tokenToCheck.instance == "Input")
  {
     tokenToCheck.tokenId = KW_tk;
  }
  else if(tokenToCheck.instance == "Output")
  {
     tokenToCheck.tokenId = KW_tk;
  }
  else if(tokenToCheck.instance == "Program")
  {
     tokenToCheck.tokenId = KW_tk;
  }
  return tokenToCheck;
}

token FADriver(ifstream &file)
{
  int state = 0; //initial state1
  int nextChar = 0; //must determine nextChar
  int seenPeriodCount = 0;
  int numberTokenCount = 0;
  int IDTokenCount = 0;
  int loopCount = 0;
  bool isStateFinal = false;
  string getNextState;
  filter filterObject;
  Stack initStack;
  Stack &commentStack = initStack;
  token tokenReturned;
  tokenReturned.lineNumber = 0;
  tokenReturned.tokenId = NULL_tk;
  while (isStateFinal == false)
  {
  loopCount++;
  filterObject = getNextChar(filterObject, file, commentStack);
  if(file.eof())
  {
     isStateFinal = true;
     tokenReturned.tokenId = EOF_tk;
     break;
  }
  if(commentStack.isEmpty())
  {
    if(!file.eof())
    {
      switch(filterObject.readChar)
        {
          case '<':
                  nextChar = 0;
                  break;
          case '>':
                  nextChar = 1;
                  break;
          case '=':
                  nextChar = 2;
                  break;
          case '!':
                  nextChar = 3;
                  break;
          case ':':
                  nextChar = 4;
                  break;
          case '+':
                  nextChar = 5;
                  break;
          case '-':
                  nextChar = 6;
                  break;
          case '*':
                  nextChar = 7;
                  break;
          case '/':
                  nextChar = 8;
                  break;
          case '&':
                  nextChar = 9;
                  break;
          case '%':
                  nextChar = 10;
                  break;
          case '.':
                  nextChar = 11;
                  break;
          case ',':
                  nextChar = 12;
                  break;
          case ';':
                  nextChar = 13;
                  break;
          case '(':
                  nextChar = 14;
                  break;
          case ')':
                  nextChar = 15;
                  break;
          case '{':
                  nextChar = 16;
                  break;
          case '}':
                  nextChar = 17;
                  break;
          case '[':
                  nextChar = 18;
                  break;
          case ']':
                  nextChar = 19;
                  break;
          case 'a':
          case 'A':
          case 'b':
          case 'B':
          case 'c':
          case 'C':
          case 'd':
          case 'D':
          case 'e':
          case 'E':
          case 'f':
          case 'F':
          case 'g':
          case 'G':
          case 'h':
          case 'H':
          case 'i':
          case 'I':
          case 'j':
          case 'J':
          case 'k':
          case 'K':
          case 'l':
          case 'L':
          case 'm':
          case 'M':
          case 'n':
          case 'N':
          case 'o':
          case 'O':
          case 'p':
          case 'P':
          case 'q':
          case 'Q':
          case 'r':
          case 'R':
          case 's':
          case 'S':
          case 't':
          case 'T':
          case 'u':
          case 'U':
          case 'v':
          case 'V':
          case 'w':
          case 'W':
          case 'x':
          case 'X':
          case 'y':
          case 'Y':
          case 'z':
          case 'Z':
                  nextChar = 20;
                  break;
          case '0':
          case '1':
          case '2':
          case '3':
          case '4':
          case '5':
          case '6':
          case '7':
          case '8':
          case '9':
                  nextChar = 21;
                  break;
          case '\n':
          case ' ':
          case '\t':
                  nextChar = 22;
                  break;
          default:
                  nextChar = 99; //99 is error case
        }//switch
        if(nextChar == 99)
        {
           tokenReturned.tokenId = ERR_tk;
           tokenReturned.instance += filterObject.readChar;
           isStateFinal = true;
           break;
        }
        getNextState = tableReader(state, nextChar);
        if(getNextState == "state2")
        {
           tokenReturned.instance += filterObject.readChar; //append char to stringInstance
           state = 1; //go to state2 [1]
        }
        else if(getNextState == "state3")
        {
           tokenReturned.instance += filterObject.readChar; //append char to stringInstance
           state = 2; //go to state3 [2]
        }
        else if(getNextState == "state6")
        {
           tokenReturned.instance += filterObject.readChar; //append char to stringInstance
           state = 5; //go to state6 [5]
        }
        else if(getNextState == "state8")
        {
           tokenReturned.instance += filterObject.readChar; //append char to stringInstance
           state = 7; //go to state8 [7]
        }
        else if(getNextState == "state10")
        {
           tokenReturned.instance += filterObject.readChar; //append char to stringInstance
           state = 9; //go to state10 [9]
           seenPeriodCount++;
        }
        else if(getNextState == "state11" && IDTokenCount > 7)
        {
           isStateFinal = true;
           tokenReturned.tokenId = IDENT_tk;
        }
        else if(getNextState == "state11")
        {
            tokenReturned.instance += filterObject.readChar; //append char to stringInstance
            state = 10; //go to state11 [10]
            IDTokenCount++;
        }
        else if((getNextState == "state12" && numberTokenCount > 7) || (getNextState == "state12" && seenPeriodCount > 1))
        {
            if(filterObject.readChar == '.')
            {
                //int length = file.tellg();
                //file.seekg((length-1), file.beg);
            }
            isStateFinal = true;
            tokenReturned.tokenId = NUM_tk;
        }
        else if(getNextState == "state12")
        {
           if(filterObject.readChar == '.' && seenPeriodCount == 1)
           {
               int length = file.tellg();
               file.seekg((length-1), file.beg);
               seenPeriodCount++;
               numberTokenCount++;
           }
           if(filterObject.readChar == '.' && seenPeriodCount == 0)
           {
              state = 11;
              tokenReturned.instance += filterObject.readChar; //append char to stringInstance
              seenPeriodCount++;
              numberTokenCount++;
           }
           else if(filterObject.readChar == '.' && seenPeriodCount > 0)
           {
              state = 11; //go to state12 [11]
              numberTokenCount++;
              seenPeriodCount++;
           }
           else
           {
              tokenReturned.instance += filterObject.readChar; //append char to stringInstance
              state = 11; //go to state12 [11]
              numberTokenCount++;
           }
        }
        else if(getNextState == "state1")
        {
           if(filterObject.readChar == '\n')
           {
              tokenReturned.lineNumber++;
           }
           state = 0; //go to state1 [0]
        }
        else if(getNextState == "state4")
        {
           tokenReturned.instance += filterObject.readChar; //append char to stringInstance
           state = 3; //go to state4 [3]
        }
        else if(getNextState == "state5")
        {
           tokenReturned.instance += filterObject.readChar; //append char to stringInstance
           state = 4; //go to state5 [4]
        }
        else if(getNextState == "state7")
        {
           tokenReturned.instance += filterObject.readChar; //append char to stringInstance
           state = 6; //go to state7 [6]
        }
        else if(getNextState == "state9")
        {
           tokenReturned.instance += filterObject.readChar; //append char to stringInstance
           state = 8; //go to state9 [8]
        }
        else if(getNextState == "FINAL <TK")
        {
           isStateFinal = true;
           tokenReturned.tokenId = OPER_tk;
        }
        else if(getNextState == "FINAL >TK")
        {
           isStateFinal = true;
           tokenReturned.tokenId = OPER_tk;
        }
        else if(getNextState == "FINAL <=TK")
        {
           isStateFinal = true;
           tokenReturned.tokenId = OPER_tk;
        }
        else if(getNextState == "FINAL >=TK")
        {
           isStateFinal = true;
           tokenReturned.tokenId = OPER_tk;
        }
        else if(getNextState == "FINAL =TK")
        {
           isStateFinal = true;
           tokenReturned.tokenId = OPER_tk;
        }
        else if(getNextState == "FINAL ==TK")
        {
           isStateFinal = true;
           tokenReturned.tokenId = OPER_tk;
        }
        else if(getNextState == "FINAL !=TK")
        {
           isStateFinal = true;
           tokenReturned.tokenId = OPER_tk;
        }
        else if(getNextState == "FINAL .TK")
        {
           isStateFinal = true;
           tokenReturned.tokenId = OPER_tk;
        }
        else if(getNextState == "FINAL IDTK")
        {
           isStateFinal = true;
           //keyword lookup here
           tokenReturned.tokenId = IDENT_tk;
        }
        else if(getNextState == "FINAL #TK")
        {
           isStateFinal = true;
           tokenReturned.tokenId = NUM_tk;
        }
        else if(getNextState == "ERROR !TK")
        {
           isStateFinal = true;
           tokenReturned.tokenId = ERR_tk;
        }
        else if(getNextState == "FINAL *TK")
        {
           tokenReturned.instance += filterObject.readChar;
           isStateFinal = true;
           tokenReturned.tokenId = OPER_tk;
        }
        else if(getNextState == "FINAL /TK")
        {
           tokenReturned.instance += filterObject.readChar;
           isStateFinal = true;
           tokenReturned.tokenId = OPER_tk;
        }
        else if(getNextState == "FINAL :TK")
        {
           tokenReturned.instance += filterObject.readChar;
           isStateFinal = true;
           tokenReturned.tokenId = OPER_tk;
        }
        else if(getNextState == "FINAL +TK")
        {
           tokenReturned.instance += filterObject.readChar;
           isStateFinal = true;
           tokenReturned.tokenId = OPER_tk;
        }
        else if(getNextState == "FINAL -TK")
        {
           tokenReturned.instance += filterObject.readChar;
           isStateFinal = true;
           tokenReturned.tokenId = OPER_tk;
        }
        else if(getNextState == "FINAL %TK")
        {
           tokenReturned.instance += filterObject.readChar;
           isStateFinal = true;
           tokenReturned.tokenId = OPER_tk;
        }
        else if(getNextState == "FINAL &TK")
        {
           tokenReturned.instance += filterObject.readChar;
           isStateFinal = true;
           tokenReturned.tokenId = OPER_tk;
        }
        else if(getNextState == "FINAL ,TK")
        {
           tokenReturned.instance += filterObject.readChar;
           isStateFinal = true;
           tokenReturned.tokenId = OPER_tk;
        }
        else if(getNextState == "FINAL ;TK")
        {
           tokenReturned.instance += filterObject.readChar;
           isStateFinal = true;
           tokenReturned.tokenId = OPER_tk;
        }
        else if(getNextState == "FINAL (TK")
        {
           tokenReturned.instance += filterObject.readChar;
           isStateFinal = true;
           tokenReturned.tokenId = OPER_tk;
        }
        else if(getNextState == "FINAL )TK")
        {
           tokenReturned.instance += filterObject.readChar;
           isStateFinal = true;
           tokenReturned.tokenId = OPER_tk;
        }
        else if(getNextState == "FINAL {TK")
        {
           tokenReturned.instance += filterObject.readChar;
           isStateFinal = true;
           tokenReturned.tokenId = OPER_tk;
        }
        else if(getNextState == "FINAL }TK")
        {
           tokenReturned.instance += filterObject.readChar;
           isStateFinal = true;
           tokenReturned.tokenId = OPER_tk;
        }
        else if(getNextState == "FINAL [TK")
        {
           tokenReturned.instance += filterObject.readChar;
           isStateFinal = true;
           tokenReturned.tokenId = OPER_tk;
        }
        else if(getNextState == "FINAL ]TK")
        {
           tokenReturned.instance += filterObject.readChar;
           isStateFinal = true;
           tokenReturned.tokenId = OPER_tk;
        }
      //cout<<"Char that was read: "<<filterObject.readChar<<endl;
        if(file.eof())
        {
          isStateFinal = true;
          break;
        }
        if(file.bad())
        {
          isStateFinal = true;
          break;
        }
        if(file.fail())
        {
          isStateFinal = true;
          break;
        }
    }//if(!file.eof())
    else if(file.eof())
    {
       isStateFinal = true;
       tokenReturned.tokenId = EOF_tk;
    }
  }//if(commentStack.isEmpty())
  else
  {
     if(file.eof())
       isStateFinal = true;
     if(filterObject.readChar == '\n')
     {
        tokenReturned.lineNumber = 1;
     }
  }
  }//while(isStateFinal != false)
  int length = file.tellg();
  if(length > 0 && state != 0)
  {
    file.seekg((length-1), file.beg);
  }
  else if(length > 0 && state == 0)
  {

  }
  if(tokenReturned.tokenId == IDENT_tk)
  {
     tokenReturned = checkForKeyword(tokenReturned);
  }
  //cout<<"token is \""<<tokenReturned.instance<<"\". tokenType: "<<tokenNamesScanner[tokenReturned.tokenId]<<endl;
  return tokenReturned;
}//FADriver()

token getNextToken(ifstream &file)
{
  //filter filterObject;
  token getToken;
  //Stack initStack;
  //Stack &commentStack = initStack;
  //while (!file.eof())
  //{
  //filterObject = getNextChar(filterObject, file, commentStack);
  //if(commentStack.isEmpty())
  getToken = FADriver(file);
    //if(!file.eof() && commentStack.isEmpty())
    //{
      //cout<<"Char that was read: "<<filterObject.readChar<<endl;
    //}
  //}
  //cout<<"here is table[2][2]: "<<table[2][2]<<endl;
  return getToken;
  //file.close();
}
