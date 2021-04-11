#include "imprimirDatos.h"

//Función que calcula los valores de P y tamanho promedio y sus desviaciones
// para las distintas simulaciones realizadas. Al final imprime los datos
// en un archivo de texto
//Param: fout archivo de escritura
//       tamanho l de la matriz y probabilidad p de llenado
//       vector guardaP que tiene los valores calculados de P(p,l)
//       vector guardaS que tiene los valores calculados de s(p,l)

void imprimirDatos ( std::ofstream & fout, int l, double p ,
		     std::vector<double> guardaP, std::vector<double> guardaS){
  double promedioTamanhos = 0;
  double promedioP = 0;
  double desvTamanhos = 0;
  double desvP = 0;

  //Calcula promedio Tamanhos
  for( int i = 0; i < guardaS.size( ); i++){
    promedioTamanhos += guardaS[i];
  }
  promedioTamanhos = promedioTamanhos/guardaS.size();
  
  //Calcula promedio P
  for( int i = 0; i < guardaP.size( ); i++){
    promedioP += guardaP[i];
  }
  promedioP = promedioP/guardaP.size();

  //Calcula desviaciones Tamanhos
  for( int i = 0; i < guardaS.size( ); i++){
    desvTamanhos += std::pow(guardaS[i]-promedioTamanhos,2);
  }
  desvTamanhos = std::sqrt(desvTamanhos/guardaS.size());

  //Calcula desviaciones P
  for( int i = 0; i < guardaP.size( ); i++){
    desvP += std::pow(guardaP[i]-promedioP,2);
  }
  desvP = std::sqrt(desvP/guardaP.size());

  fout.precision(4); fout.setf(std::ios::scientific);
  fout << l << "\t\t" << p << "\t\t" << promedioP << "\t\t" <<desvP  <<
    "\t\t" << promedioTamanhos  << "\t\t" << desvTamanhos << std::endl;
}
