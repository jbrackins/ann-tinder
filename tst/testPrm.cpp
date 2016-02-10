#include <iostream>
#include "../inc/Prm.h"
#include <string>

using namespace std;

int main(int argc, char**argv)
{ 

  printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

  Prm * p = new Prm( argv[1] );

  //Read in a .prm file  
  p->readPrm();

  //Verify .prm was read into class
  p->printPrm();
  
  printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

  //Verify that .prm writing works
  p->setFilename( "prm/testWriter.prm" );
  p->writePrm();
  
  //Should be identical to previous
  Prm * tst = new Prm( "prm/testWriter.prm" );
  tst->readPrm();
  tst->printPrm();

  printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

  return 0;

}
