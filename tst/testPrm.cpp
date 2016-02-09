#include <iostream>
#include "../inc/Prm.h"
#include <string>

using namespace std;

int main(int argc, char**argv)
{ 

  Prm * p = new Prm( argv[1] );

  //Read in a .prm file  
  p->readPrm();

  //Verify .prm was read into class
  p->printPrm();
  
  //Verify that .prm writing works
  p->setFilename( "prm/testWriter.prm" );
  p->writePrm();

  return 0;

}
