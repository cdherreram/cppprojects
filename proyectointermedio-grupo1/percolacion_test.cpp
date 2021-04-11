#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch2/catch.hpp"
//#include "catch.hpp"

#include "percolacion.h"
#include "clusters.h"
#include "generacionMallaAleatoria.h"

//se hace el test con varias matrices
TEST_CASE( "Percolacion de matrices" ) {
Eigen::MatrixXd O(10,10);
Eigen::MatrixXd Z(10,10);
Eigen::MatrixXd F(20,20);
for(int i=0; i< F.cols();i++){
  for(int j=0; j< F.cols(); j++){
    if(i == 0) {
      F(i,j) = 0;
    }else{
      F(i,j) =1;
    }
    if(j==0) F(i,j)=0;
    if (i == F.cols()-1) F(i,j)=0;
    if(j == F.cols()-1) F(i,j)=0;

  }
}

generacionMallaAleatoria(O,0,1);
generacionMallaAleatoria(Z,0,0);
    REQUIRE( percolacion(O) !=  0 );    
    REQUIRE( percolacion(Z) ==  0 );
    REQUIRE( percolacion(F) == 0);
}
