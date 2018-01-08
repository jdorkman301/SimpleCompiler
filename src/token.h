#include <string>

#ifndef TOKEN_H
#define TOKEN_H

using namespace std;

enum tokenID {IDENT_tk, NUM_tk, KW_tk, OPER_tk, EOF_tk, NULL_tk, ERR_tk};

struct token
{
  tokenID tokenId;
  string instance;
  string label;
  int level;
  int lineNumber;
  struct token *childSubtree1;
  struct token *childSubtree2;
  struct token *childSubtree3;
  struct token *childSubtree4;
  struct token *childSubtree5;
  struct token *childSubtree6;
  struct token *childSubtree7;
};

extern token* head;

#endif
