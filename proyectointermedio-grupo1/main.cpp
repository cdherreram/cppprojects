#include <eigen3/Eigen/Dense>
#include <fstream>
#include <vector>
#include "generacionMallaAleatoria.h"
#include "percolacion.h"
#include "clusters.h"
#include "imprimirDatos.h"
#include "calculoPyS.h"

int main ( void )
{
  int tamanho = 0;
  std::ofstream fout;
  Eigen::VectorXd v(20);
  Eigen::VectorXd datosPyS(2);
  std::vector<double> guardaP;
  std::vector<double> guardaS;
  fout.open("datos1.txt");
  fout << "#L \t\t\t p \t\t\t Pmean \t\t\t Pstd \t\t\t smean \t\t\t sstd" << std::endl;
  for ( int l = 32; l <= 512; l *= 2 ){
    for ( double p = 0.41; p < 0.71; p += 0.01 ){
      for( int n = 1; n < 4000; n += 50 ){
	//    1, 50, 100, 167
	for ( int i= 0; i < 20 ; i++){
	  int seed = n + i;
	  Eigen::MatrixXd m(l,l);
	  generacionMallaAleatoria( m ,seed, p);
	  tamanho = percolacion( m );
	  v( i ) = tamanho;
	}
	datosPyS = calculoPyS( v , l );
	guardaP.push_back(datosPyS(0));
	guardaS.push_back(datosPyS(1));
	v.setZero();
	datosPyS.setZero();
      }
      imprimirDatos(fout, l, p,guardaP, guardaS);
      guardaP.clear();
      guardaS.clear(); 
    }
  }
  return 0;
}
