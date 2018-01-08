#include <cstddef>
#include <iostream>
#include "varStack.h"

#ifndef TESTTREE_H
#define TESTTREE_H

  token* insertNode( token* );
  void codeGen( token*, int, varStack*, varStack*, ofstream&);
  token* getNode(string);

#endif
