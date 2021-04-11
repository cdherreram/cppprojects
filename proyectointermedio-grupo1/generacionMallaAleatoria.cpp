#include "generacionMallaAleatoria.h"

//Matriz para llenar segun la probabilidad
//Param: Matriz (como puntero)
//       Valor de semilla
//       probabilidad p
void generacionMallaAleatoria(Eigen::MatrixXd & m, int semilla, double prob){
  std::mt19937 gen(semilla);
  std::binomial_distribution<> dis(1,prob);
  for(int i = 0; i < m.cols(); i++){
    for(int j = 0; j < m.cols(); j++){
      m(i,j) = dis(gen);
    }
  }
}
