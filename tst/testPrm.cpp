#include <iostream>
#include "../inc/Prm.h"
#include <string>

using namespace std;

int main(int argc, char**argv)
{ 

  printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

  Prm param = Prm(argv[1]);
  //Prm * p = new Prm( argv[1] );

  //Read in a .prm file  
  param.readPrm();

  //Verify .prm was read into class
  param.printPrm();
  
  printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

  //Verify that .prm writing works
  param.setFilename( "prm/testWriter.prm" );
  param.writePrm();
  
  //Should be identical to previous
  Prm tst = Prm( "prm/testWriter.prm" );
  tst.readPrm();
  tst.printPrm();

  printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");


  return 0;


}
