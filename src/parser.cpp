#include <iostream>
#include <fstream>
#include <string>
#include "parser.h"
#include "scanner.h"
#include "token.h"
#include "filter.h"
#include "testTree.h"

using namespace std;

string tokenNames[] = {"Identifier", "Number", "Keyword", "Operator", "EndOfFile"};

//globals
int lineNumber = 1;
token nextToken;


token setLineNumber(token &lnToken)
{
  if(lnToken.lineNumber != 0)
  {
     lineNumber++;
  }
  return lnToken;
}

token* parser(ifstream &file)
{
  /*token nextToken;
  int lineNumber = 1;
  bool error = false;
  while((!file.eof()) && (error == false))
  {
    nextToken = getNextToken(file);
    if(nextToken.lineNumber != 0)
    {
       lineNumber++;
       nextToken.lineNumber = lineNumber;
    }
    if((nextToken.tokenId != NULL_tk) && (nextToken.tokenId != ERR_tk))
    {
       cout<<"Found "<<tokenNames[nextToken.tokenId]<<" token: '"<<nextToken.instance<<"' on line number: "<<lineNumber<<endl;
    }
    if(nextToken.tokenId == ERR_tk)
    {
       cout<<"Error: '"<<nextToken.instance<<"' on line "<<lineNumber<<" is invalid token or illegal character"<<endl;
       error = true;
    }
  }*/

  //token *headNode;
  //headNode = new token;
  //head = insertNode(headNode);
  //head from extern token* head
  //in token.h

  //token *nextNode;
  //nextNode = new token;
  //nextNode->label = "nextNode";
  //nextNode->instance = "nodeToken";
  //nextNode->tokenId = NULL_tk;
  //nextNode->lineNumber = 0;
  //nextNode->level = 0;
  //head = insertNode(nextNode);

  nextToken = getNextToken(file);
  nextToken = setLineNumber(nextToken);
  head = Program(file);
  if((nextToken.tokenId != NULL_tk) && (nextToken.tokenId != ERR_tk))
  {
    if(nextToken.tokenId == EOF_tk)
    {
      cout<<"Parse OK"<<endl;
      head->instance = "";
      return head;
    }
    else if(nextToken.tokenId == ERR_tk)
    {
      cout<<nextToken.instance<<endl;
    }
    else
    {
      cout<<"ERROR:LINE:"<<lineNumber<<":expected EOF_tk and received \"";
      cout<<nextToken.instance<<"\" on line: ";
      cout<<nextToken.lineNumber<<endl;
      head->instance = "error";
      return head;
    }
  }
  file.close();
  cout<<"\""<<nextToken.instance<<endl;
  head->instance = "error";
  return head;
}

token* Program(ifstream &file)
{
  token* p = getNode("Program");
  p->childSubtree1 = Vars(file);

  if(nextToken.tokenId != ERR_tk)
    p->childSubtree2 = Block(file);

  return p;
}

token* Vars(ifstream &file)
{
  token* varsNodeParent = getNode("Vars");
  if(nextToken.instance == "Var")//there are vars. Expected Var and Identifier
  {                              //terminals
    token* varNode = getNode("Var");
    varNode->instance = nextToken.instance;
    varNode->tokenId = nextToken.tokenId;
    varNode->lineNumber = nextToken.lineNumber;
    varsNodeParent->childSubtree1 = varNode;
    nextToken = getNextToken(file);
    nextToken = setLineNumber(nextToken);
  }//found token, consume
  else//empty set -- no var
  {
    return nullptr;
  }

  if(nextToken.tokenId == IDENT_tk)
  {
    token* identNode = getNode("Identifier");
    identNode->instance = nextToken.instance;
    identNode->tokenId = nextToken.tokenId;
    identNode->lineNumber = nextToken.lineNumber;
    varsNodeParent->childSubtree2 = identNode;
    nextToken = getNextToken(file);
    nextToken = setLineNumber(nextToken);
    varsNodeParent->childSubtree3 = Mvars(file);
  }//matches IDENT_tk, consume and call mVars
  else
  {
    cout<<"ERROR:LINE:"<<lineNumber<<": expected Identifier token but got: ";
    nextToken.instance += "\"";
    nextToken.tokenId = ERR_tk;
    return nullptr;
  }//terminate

  return varsNodeParent;
}

token* Block(ifstream &file)
{
  token* blockNodeParent = getNode("Block");
  if(nextToken.instance == "Begin")//expected Begin terminal
  {
    token* beginNode = getNode("Begin");
    beginNode->instance = nextToken.instance;
    beginNode->tokenId = nextToken.tokenId;
    beginNode->lineNumber = nextToken.lineNumber;
    blockNodeParent->childSubtree1 = beginNode;
    nextToken = getNextToken(file);
    nextToken = setLineNumber(nextToken);
  }//found Begin, consume token
  else//ERR: Begin terminal required
  {
    cout<<"ERROR:LINE:"<<lineNumber<<" no Begin token. Got: ";
    nextToken.instance += "\"";
    nextToken.tokenId = ERR_tk;
    return nullptr;
  }

  //above executed successfully, call Vars
  if(nextToken.tokenId != ERR_tk)
  {
    blockNodeParent->childSubtree2 = Vars(file);
  }


  //if no error from calling Vars, call Stats
  if(nextToken.tokenId != ERR_tk)
  {
    blockNodeParent->childSubtree3 = Stats(file);
  }

  if(nextToken.tokenId != ERR_tk)
  {
    if(nextToken.instance == "End")
    {
      token* endNode = getNode("End");
      endNode->instance = nextToken.instance;
      endNode->tokenId = nextToken.tokenId;
      endNode->lineNumber = nextToken.lineNumber;
      blockNodeParent->childSubtree4 = endNode;
      nextToken = getNextToken(file);
      nextToken = setLineNumber(nextToken);
    }
    else
    {
      cout<<"ERROR:LINE:"<<lineNumber<<" no End token. Got: ";
      nextToken.instance += "\"";
      nextToken.tokenId = ERR_tk;
      return nullptr;
    }
  }

  return blockNodeParent;
}

token* Mvars(ifstream &file)
{
  token* mvarsParent = getNode("Mvars");
  if(nextToken.instance == ".")
  {
    token* periodNode = getNode("Period");
    periodNode->instance = nextToken.instance;
    periodNode->tokenId = nextToken.tokenId;
    periodNode->lineNumber = nextToken.lineNumber;
    mvarsParent->childSubtree1 = periodNode;
    nextToken = getNextToken(file);
    nextToken = setLineNumber(nextToken);
    return mvarsParent;
  }//found ., consume and return

  if(nextToken.instance == ",")
  {
    token* commaNode = getNode("Comma");
    commaNode->instance = nextToken.instance;
    commaNode->tokenId = nextToken.tokenId;
    commaNode->lineNumber = nextToken.lineNumber;
    mvarsParent->childSubtree1 = commaNode;
    nextToken = getNextToken(file);
    nextToken = setLineNumber(nextToken);
  }//found ,, consume

  if(nextToken.tokenId == IDENT_tk)
  {
    token* identNode = getNode("Identifier");
    identNode->instance = nextToken.instance;
    identNode->tokenId = nextToken.tokenId;
    identNode->lineNumber = nextToken.lineNumber;
    mvarsParent->childSubtree2 = identNode;
    nextToken = getNextToken(file);
    nextToken = setLineNumber(nextToken);
  }//found Identifier, consume
  else
  {
    cout<<"ERROR:LINE:"<<lineNumber<<" expected Identifier. Got: ";
    nextToken.instance += "\"";
    nextToken.tokenId = ERR_tk;
    return nullptr;
  }

  if(nextToken.tokenId != ERR_tk)
  {
    mvarsParent->childSubtree3 = Mvars(file);
  }

  return mvarsParent;
}

token* Stats(ifstream &file)
{
  token* statsParent = getNode("Stats");
  statsParent->childSubtree1 = Stat(file);

  if(nextToken.tokenId != ERR_tk)
  {
    statsParent->childSubtree2 = Mstat(file);
  }

  return statsParent;
}

token* Stat(ifstream &file)
{
  token* statParent = getNode("Stat");
  if(nextToken.instance == "Input")
  {
    statParent->childSubtree1 = In(file);
  }
  else if(nextToken.instance == "Output")
  {
    statParent->childSubtree1 = Out(file);
  }
  else if(nextToken.instance == "Begin")
  {
    statParent->childSubtree1 = Block(file);
  }
  else if(nextToken.instance == "Check")
  {
    statParent->childSubtree1 = If(file);
  }
  else if(nextToken.instance == "Loop")
  {
    statParent->childSubtree1 = Loop(file);
  }
  else if(nextToken.tokenId == IDENT_tk)
  {
    statParent->childSubtree1 = Assign(file);
  }
  else
  {
    cout<<"ERROR:LINE:"<<lineNumber<<" expected \"Input\",\"Output\",\"Begin\",\"Check\",";
    cout<<"\"Loop\", or \"Identifier\". Got: ";
    nextToken.instance += "\"";
    nextToken.tokenId = ERR_tk;
    return nullptr;
  }

  return statParent;
}

token* Mstat(ifstream &file)
{
  token* mstatParent = getNode("Mstat");
  if(nextToken.instance == "Input")
  {
    mstatParent->childSubtree1 = Stat(file);
    if(nextToken.tokenId != ERR_tk)
    {
      mstatParent->childSubtree2 = Mstat(file);
    }
  }
  else if(nextToken.instance == "Output")
  {
    mstatParent->childSubtree1 = Stat(file);
    if(nextToken.tokenId != ERR_tk)
    {
      mstatParent->childSubtree2 = Mstat(file);
    }
  }
  else if(nextToken.instance == "Begin")
  {
    mstatParent->childSubtree1 = Stat(file);
    if(nextToken.tokenId != ERR_tk)
    {
      mstatParent->childSubtree2 = Mstat(file);
    }
  }
  else if(nextToken.instance == "Check")
  {
    mstatParent->childSubtree1 = Stat(file);
    if(nextToken.tokenId != ERR_tk)
    {
      mstatParent->childSubtree2 = Mstat(file);
    }
  }
  else if(nextToken.instance == "Loop")
  {
    mstatParent->childSubtree1 = Stat(file);
    if(nextToken.tokenId != ERR_tk)
    {
      mstatParent->childSubtree2 = Mstat(file);
    }
  }
  else if(nextToken.tokenId == IDENT_tk)
  {
    mstatParent->childSubtree1 = Stat(file);
    if(nextToken.tokenId != ERR_tk)
    {
      mstatParent->childSubtree2 = Mstat(file);
    }
  }
  else
  {//empty, just return
    return nullptr;
  }

  return mstatParent;
}

token* In(ifstream &file)
{
  token* inParent = getNode("In");
  if(nextToken.instance == "Input")
  {
    token* inputNode = getNode("Input");
    inputNode->instance = nextToken.instance;
    inputNode->tokenId = nextToken.tokenId;
    inputNode->lineNumber = nextToken.lineNumber;
    inParent->childSubtree1 = inputNode;
    nextToken = getNextToken(file);
    nextToken = setLineNumber(nextToken);
  }//found Input, consume
  else
  {
    cout<<"ERROR:LINE:"<<lineNumber<<" expected \"Input\". Got: ";
    nextToken.instance += "\"";
    nextToken.tokenId = ERR_tk;
    return nullptr;
  }

  if(nextToken.tokenId == IDENT_tk)
  {
    token* identNode = getNode("Identifier");
    identNode->instance = nextToken.instance;
    identNode->tokenId = nextToken.tokenId;
    identNode->lineNumber = nextToken.lineNumber;
    inParent->childSubtree2 = identNode;
    nextToken = getNextToken(file);
    nextToken = setLineNumber(nextToken);
  }//found Identifier, consume
  else
  {
    cout<<"ERROR:LINE:"<<lineNumber<<" expected \"Identifier\". Got: ";
    nextToken.instance += "\"";
    nextToken.tokenId = ERR_tk;
    return nullptr;
  }

  if(nextToken.instance == ";")
  {
    token* semicolonNode = getNode("Semicolon");
    semicolonNode->instance = nextToken.instance;
    semicolonNode->tokenId = nextToken.tokenId;
    semicolonNode->lineNumber = nextToken.lineNumber;
    inParent->childSubtree3 = semicolonNode;
    nextToken = getNextToken(file);
    nextToken = setLineNumber(nextToken);
    return inParent;
  }
  else
  {
    cout<<"ERROR:LINE:"<<lineNumber<<" expected \";\". Got: ";
    nextToken.instance += "\"";
    nextToken.tokenId = ERR_tk;
    return nullptr;
  }

  return inParent;
}

token* Out(ifstream &file)
{
  token* outParent = getNode("Out");
  if(nextToken.instance == "Output")
  {
    token* outputNode = getNode("Output");
    outputNode->instance = nextToken.instance;
    outputNode->tokenId = nextToken.tokenId;
    outputNode->lineNumber = nextToken.lineNumber;
    outParent->childSubtree1 = outputNode;
    nextToken = getNextToken(file);
    nextToken = setLineNumber(nextToken);
  }//found Output, consume
  else
  {
    cout<<"ERROR:LINE:"<<lineNumber<<" expected \"Output\". Got: ";
    nextToken.tokenId = ERR_tk;
    return nullptr;
  }

  if(nextToken.tokenId != ERR_tk)
  {
    outParent->childSubtree2 = Expr(file);
  }

  if(nextToken.instance == ";")
  {
    token* semicolonNode = getNode("Semicolon");
    semicolonNode->instance = nextToken.instance;
    semicolonNode->tokenId = nextToken.tokenId;
    semicolonNode->lineNumber = nextToken.lineNumber;
    outParent->childSubtree3 = semicolonNode;
    nextToken = getNextToken(file);
    nextToken = setLineNumber(nextToken);
  }//found ;, consume
  else
  {
    cout<<"ERROR:LINE:"<<lineNumber<<" expected \";\". Got: ";
    nextToken.tokenId = ERR_tk;
    nextToken.instance += "\"";
    return nullptr;
  }

  return outParent;
}

token* If(ifstream &file)
{
  token* ifParent = getNode("If");
  if(nextToken.instance == "Check")
  {
    token* checkNode = getNode("Check");
    checkNode->instance = nextToken.instance;
    checkNode->tokenId = nextToken.tokenId;
    checkNode->lineNumber = nextToken.lineNumber;
    ifParent->childSubtree1 = checkNode;
    nextToken = getNextToken(file);
    nextToken = setLineNumber(nextToken);
  }
  else
  {
    cout<<"ERROR:LINE:"<<lineNumber<<" expected \"Check\". Got: ";
    nextToken.tokenId = ERR_tk;
    nextToken.instance += "\"";
    return nullptr;
  }

  if(nextToken.instance == "[")
  {
    token* openBracketNode = getNode("Open Bracket");
    openBracketNode->instance = nextToken.instance;
    openBracketNode->tokenId = nextToken.tokenId;
    openBracketNode->lineNumber = nextToken.lineNumber;
    ifParent->childSubtree2 = openBracketNode;
    nextToken = getNextToken(file);
    nextToken = setLineNumber(nextToken);
    if(nextToken.tokenId != ERR_tk)
    {
      ifParent->childSubtree3 = Expr(file);
    }
  }
  else
  {
    cout<<"ERROR:LINE:"<<lineNumber<<" expected \"[\". Got: ";
    nextToken.tokenId = ERR_tk;
    nextToken.instance += "\"";
    return nullptr;
  }

  if(nextToken.tokenId != ERR_tk)
  {
    ifParent->childSubtree4 = RO(file);
  }

  if(nextToken.tokenId != ERR_tk)
  {
    ifParent->childSubtree5 = Expr(file);
  }

  if(nextToken.instance == "]")
  {
    token* closeBracketNode = getNode("Close Bracket");
    closeBracketNode->instance = nextToken.instance;
    closeBracketNode->tokenId = nextToken.tokenId;
    closeBracketNode->lineNumber = nextToken.lineNumber;
    ifParent->childSubtree6 = closeBracketNode;
    nextToken = getNextToken(file);
    nextToken = setLineNumber(nextToken);
  }
  else
  {
    if(nextToken.tokenId != ERR_tk)
    {
      cout<<"ERROR:LINE:"<<lineNumber<<" expected \"]\". Got: ";
      nextToken.tokenId = ERR_tk;
      nextToken.instance += "\"";
    }
    return nullptr;
  }

  if(nextToken.tokenId != ERR_tk)
  {
    ifParent->childSubtree7 = Stat(file);
  }

  return ifParent;
}

token* Loop(ifstream &file)
{
  token* loopParent = getNode("Loop");
  if(nextToken.instance == "Loop")
  {
    token* loopNode = getNode("Loop");
    loopNode->instance = nextToken.instance;
    loopNode->tokenId = nextToken.tokenId;
    loopNode->lineNumber = nextToken.lineNumber;
    loopParent->childSubtree1 = loopNode;
    nextToken = getNextToken(file);
    nextToken = setLineNumber(nextToken);
  }
  else
  {
    cout<<"ERROR:LINE:"<<lineNumber<<" expected \"Loop\". Got: ";
    nextToken.tokenId = ERR_tk;
    nextToken.instance += "\"";
    return nullptr;
  }

  if(nextToken.instance == "[")
  {
    token* openBracketNode = getNode("Open Bracket");
    openBracketNode->instance = nextToken.instance;
    openBracketNode->tokenId = nextToken.tokenId;
    openBracketNode->lineNumber = nextToken.lineNumber;
    loopParent->childSubtree2 = openBracketNode;
    nextToken = getNextToken(file);
    nextToken = setLineNumber(nextToken);
    if(nextToken.tokenId != ERR_tk)
    {
      loopParent->childSubtree3 = Expr(file);
    }
  }
  else
  {
    cout<<"ERROR:LINE:"<<lineNumber<<" expected \"[\". Got: ";
    nextToken.tokenId = ERR_tk;
    nextToken.instance += "\"";
    return nullptr;
  }

  if(nextToken.tokenId != ERR_tk)
  {
    loopParent->childSubtree4 = RO(file);
  }

  if(nextToken.tokenId != ERR_tk)
  {
    loopParent->childSubtree5 = Expr(file);
  }

  if(nextToken.instance == "]")
  {
    token* closeBracketNode = getNode("Close Bracket");
    closeBracketNode->instance = nextToken.instance;
    closeBracketNode->tokenId = nextToken.tokenId;
    closeBracketNode->lineNumber = nextToken.lineNumber;
    loopParent->childSubtree6 = closeBracketNode;
    nextToken = getNextToken(file);
    nextToken = setLineNumber(nextToken);
  }
  else
  {
    cout<<"LOOP:ERROR:LINE:"<<lineNumber<<" expected \"]\". Got: ";
    nextToken.tokenId = ERR_tk;
    nextToken.instance += "\"";
    return nullptr;
  }

  if(nextToken.tokenId != ERR_tk)
  {
    loopParent->childSubtree7 = Stat(file);
  }

  return loopParent;
}

token* Assign(ifstream &file)
{
  token* assignParent = getNode("Assign");
  if(nextToken.tokenId == IDENT_tk)
  {
    token* identNode = getNode("Identifier");
    identNode->instance = nextToken.instance;
    identNode->tokenId = nextToken.tokenId;
    identNode->lineNumber = nextToken.lineNumber;
    assignParent->childSubtree1 = identNode;
    nextToken = getNextToken(file);
    nextToken = setLineNumber(nextToken);
  }//found Identifier, consume
  else
  {
    cout<<"ERROR:LINE:"<<lineNumber<<" expected \"Identifier\". Got: ";
    nextToken.instance += "\"";
    nextToken.tokenId = ERR_tk;
    return nullptr;
  }

  if(nextToken.instance == ":")
  {
    token* colonNode = getNode("Colon");
    colonNode->instance = nextToken.instance;
    colonNode->tokenId = nextToken.tokenId;
    colonNode->lineNumber = nextToken.lineNumber;
    assignParent->childSubtree2 = colonNode;
    nextToken = getNextToken(file);
    nextToken = setLineNumber(nextToken);
    if(nextToken.tokenId != ERR_tk)
    {
      assignParent->childSubtree3 = Expr(file);
    }
  }//found Input, consume
  else
  {
    cout<<"ERROR:LINE:"<<lineNumber<<" expected \":\". Got: ";
    nextToken.instance += "\"";
    nextToken.tokenId = ERR_tk;
    return nullptr;
  }

  if(nextToken.instance == ";")
  {
    token* semicolonNode = getNode("Semicolon");
    semicolonNode->instance = nextToken.instance;
    semicolonNode->tokenId = nextToken.tokenId;
    semicolonNode->lineNumber = nextToken.lineNumber;
    assignParent->childSubtree4 = semicolonNode;
    nextToken = getNextToken(file);
    nextToken = setLineNumber(nextToken);
  }
  else
  {
    cout<<"ERROR:LINE:"<<lineNumber<<" expected \";\". Got: ";
    nextToken.instance += "\"";
    nextToken.tokenId = ERR_tk;
    return nullptr;
  }

  return assignParent;
}

token* Expr(ifstream &file)
{
  token* exprParent = getNode("Expr");
  exprParent->childSubtree1 = M(file);

  if(nextToken.instance == "+")
  {
    token* plusNode = getNode("Plus");
    plusNode->instance = nextToken.instance;
    plusNode->tokenId = nextToken.tokenId;
    plusNode->lineNumber = nextToken.lineNumber;
    exprParent->childSubtree2 = plusNode;
    nextToken = getNextToken(file);
    nextToken = setLineNumber(nextToken);
    if(nextToken.tokenId != ERR_tk)
    {
      exprParent->childSubtree3 = Expr(file);
    }
  }//found +, consume
  else if(nextToken.instance == "-")
  {
    token* minusNode = getNode("Minus");
    minusNode->instance = nextToken.instance;
    minusNode->tokenId = nextToken.tokenId;
    minusNode->lineNumber = nextToken.lineNumber;
    exprParent->childSubtree2 = minusNode;
    nextToken = getNextToken(file);
    nextToken = setLineNumber(nextToken);
    if(nextToken.tokenId != ERR_tk)
    {
      exprParent->childSubtree3 = Expr(file);
    }
  }//found -, consume

  return exprParent;
}

token* M(ifstream &file)
{
  token* mParent = getNode("M");
  mParent->childSubtree1 = F(file);

  if(nextToken.instance == "%")
  {
    token* modulusNode = getNode("Modulus");
    modulusNode->instance = nextToken.instance;
    modulusNode->tokenId = nextToken.tokenId;
    modulusNode->lineNumber = nextToken.lineNumber;
    mParent->childSubtree2 = modulusNode;
    nextToken = getNextToken(file);
    nextToken = setLineNumber(nextToken);
    if(nextToken.tokenId != ERR_tk)
    {
      mParent->childSubtree3 = M(file);
    }
  }//found %, consume
  else if(nextToken.instance == "*")
  {
    token* multiplyNode = getNode("Multiply");
    multiplyNode->instance = nextToken.instance;
    multiplyNode->tokenId = nextToken.tokenId;
    multiplyNode->lineNumber = nextToken.lineNumber;
    mParent->childSubtree2 = multiplyNode;
    nextToken = getNextToken(file);
    nextToken = setLineNumber(nextToken);
    if(nextToken.tokenId != ERR_tk)
    {
      mParent->childSubtree3 = M(file);
    }
  }//found *, consume

  return mParent;
}

token* F(ifstream &file)
{
  token* fParent = getNode("F");
  if(nextToken.instance == "(")
  {
    token* openParanthesisNode = getNode("Open Paranthesis");
    openParanthesisNode->instance = nextToken.instance;
    openParanthesisNode->tokenId = nextToken.tokenId;
    openParanthesisNode->lineNumber = nextToken.lineNumber;
    fParent->childSubtree1 = openParanthesisNode;
    nextToken = getNextToken(file);
    nextToken = setLineNumber(nextToken);
    fParent->childSubtree2 = F(file);
  }//found (, consume

  if(nextToken.instance == ")")
  {
    token* closeParanthesisNode = getNode("close Paranthesis");
    closeParanthesisNode->instance = nextToken.instance;
    closeParanthesisNode->tokenId = nextToken.tokenId;
    closeParanthesisNode->lineNumber = nextToken.lineNumber;
    fParent->childSubtree3 = closeParanthesisNode;
    nextToken = getNextToken(file);
    nextToken = setLineNumber(nextToken);
    return fParent;
  }//found (, consume

  if((nextToken.instance != "(") && (nextToken.instance != ")"))
  {
    fParent->childSubtree1 = R(file);
  }

  return fParent;
}

token* R(ifstream &file)
{
  token* rParent = getNode("R");
  if(nextToken.instance == "[")
  {
    token* openBracketNode = getNode("Open Bracket");
    openBracketNode->instance = nextToken.instance;
    openBracketNode->tokenId = nextToken.tokenId;
    openBracketNode->lineNumber = nextToken.lineNumber;
    rParent->childSubtree1 = openBracketNode;
    nextToken = getNextToken(file);
    nextToken = setLineNumber(nextToken);
    rParent->childSubtree2 = Expr(file);
  }//found [, consume

  if(nextToken.instance == "]")
  {
    token* closeBracketNode = getNode("Close Bracket");
    closeBracketNode->instance = nextToken.instance;
    closeBracketNode->tokenId = nextToken.tokenId;
    closeBracketNode->lineNumber = nextToken.lineNumber;
    rParent->childSubtree3 = closeBracketNode;
    nextToken = getNextToken(file);
    nextToken = setLineNumber(nextToken);
    return rParent;
  }//found ], consume

  if(nextToken.tokenId == IDENT_tk)
  {
    token* identNode = getNode("Identifier");
    identNode->instance = nextToken.instance;
    identNode->tokenId = nextToken.tokenId;
    identNode->lineNumber = nextToken.lineNumber;
    rParent->childSubtree1 = identNode;
    nextToken = getNextToken(file);
    nextToken = setLineNumber(nextToken);
  }//found Identifier, consume
  else if(nextToken.tokenId == NUM_tk)
  {
    token* numNode = getNode("Number");
    numNode->instance = nextToken.instance;
    numNode->tokenId = nextToken.tokenId;
    numNode->lineNumber = nextToken.lineNumber;
    rParent->childSubtree1 = numNode;
    nextToken = getNextToken(file);
    nextToken = setLineNumber(nextToken);
  }//found Number, consume
  else
  {
    cout<<"R:ERROR:LINE:"<<lineNumber<<" expected \"Identifier\" or \"Number\". Got: "<<nextToken.instance;
    nextToken.instance += "\"";
    nextToken.tokenId = ERR_tk;
    return nullptr;
  }

  return rParent;
}

token* RO(ifstream &file)
{
  token* roParent = getNode("RO");
  if(nextToken.instance == "<")
  {
    token* lessNode = getNode("Less Than");
    lessNode->instance = nextToken.instance;
    lessNode->tokenId = nextToken.tokenId;
    lessNode->lineNumber = nextToken.lineNumber;
    roParent->childSubtree1 = lessNode;
    nextToken = getNextToken(file);
    nextToken = setLineNumber(nextToken);
  }//found <, consume
  else if(nextToken.instance == "<=")
  {
    token* lessENode = getNode("Less Than Equal");
    lessENode->instance = nextToken.instance;
    lessENode->tokenId = nextToken.tokenId;
    lessENode->lineNumber = nextToken.lineNumber;
    roParent->childSubtree1 = lessENode;
    nextToken = getNextToken(file);
    nextToken = setLineNumber(nextToken);
  }//found <=, consume
  else if(nextToken.instance == ">")
  {
    token* greaterNode = getNode("Greater Than");
    greaterNode->instance = nextToken.instance;
    greaterNode->tokenId = nextToken.tokenId;
    greaterNode->lineNumber = nextToken.lineNumber;
    roParent->childSubtree1 = greaterNode;
    nextToken = getNextToken(file);
    nextToken = setLineNumber(nextToken);
  }//found >, consume
  else if(nextToken.instance == ">=")
  {
    token* greaterENode = getNode("Greater Than Equal");
    greaterENode->instance = nextToken.instance;
    greaterENode->tokenId = nextToken.tokenId;
    greaterENode->lineNumber = nextToken.lineNumber;
    roParent->childSubtree1 = greaterENode;
    nextToken = getNextToken(file);
    nextToken = setLineNumber(nextToken);
  }//found >=, consume
  else if(nextToken.instance == "==")
  {
    token* equalNode = getNode("Equal Equal");
    equalNode->instance = nextToken.instance;
    equalNode->tokenId = nextToken.tokenId;
    equalNode->lineNumber = nextToken.lineNumber;
    roParent->childSubtree1 = equalNode;
    nextToken = getNextToken(file);
    nextToken = setLineNumber(nextToken);
  }//found ==, consume
  else if(nextToken.instance == "!=")
  {
    token* notEqualNode = getNode("Not Equal");
    notEqualNode->instance = nextToken.instance;
    notEqualNode->tokenId = nextToken.tokenId;
    notEqualNode->lineNumber = nextToken.lineNumber;
    roParent->childSubtree1 = notEqualNode;
    nextToken = getNextToken(file);
    nextToken = setLineNumber(nextToken);
  }//found !=, consume
  else
  {
    cout<<"ERROR:LINE:"<<lineNumber<<" expected Operator. Got: ";
    nextToken.instance += "\"";
    nextToken.tokenId = ERR_tk;
    return nullptr;
  }//found <, consume

  return roParent;
}
