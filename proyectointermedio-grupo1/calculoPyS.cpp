#include "calculoPyS.h"

Eigen::VectorXd calculoPyS ( Eigen::VectorXd v , int l){
  int conteo = 0;
  double suma = 0;
  Eigen::VectorXd salida(2);
  salida.setZero();
  for ( int i = 0; i < v.size(); i++){
    if ( v(i) != 0 ) conteo++;
  }
  salida(0) = conteo*1.0 / v.size(); //P
  suma = v.sum();
  if ( conteo != 0 ) salida(1) = suma*1.0 / (conteo*l*l); //Promedio tamanhos
  return salida;
}
