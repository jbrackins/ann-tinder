#include <iostream>
#include "../inc/Prm.h"
#include <string>

using namespace std;

int main(int argc, char**argv)
{ 

  Prm * p = new Prm( argv[1] );
  
  p->readPrm();

  p->printPrm();
  
  return 0;

}
