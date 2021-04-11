#include <iostream>
#include <cmath>
#include <vector>
#include "Cuarto.h"
#include "Individuo.h"
#include "Organizador.h"

void sistemaRadioProbabilidad(Organizador & organizador, double radioContagio, double probabilidadContagio);
void vaciarSistema(Organizador & organizador );

int main(void){
  double dt = 0.05;
  double dRadio = 0.2;
  double dProb = 0.03;
  int JMAX = 2;
  int IMAX = 2;
  Organizador org1;

  for( int ii = 0; ii < IMAX; ii++ ){
    double radio = 1.5 + ( ii * dRadio );
    for( int jj = 0; jj < JMAX; jj++ ){
      double probabilidad = 0.08 + ( jj * dProb );
      org1.InicializarPorDefecto(100,6,2); //Individuos, infectados
      org1.InicializarPosiciones(22.5);
      for ( auto * cuarto : org1.vectorCuartos ){
	cuarto->setDimensionCuartoX( 22.51 );
	cuarto->setDimensionCuartoY( 22.36 );
      }
      std::cout << "No Individuos:  " << org1.vectorIndividuos.size() << std::endl;
      
      org1.InicializarPosiciones(22.5);
      sistemaRadioProbabilidad(org1, radio, probabilidad);
      org1.EmpezarEvolucion(dt, 30, 200, 2 , true, probabilidad, radio); //dt, pasosContagio, pasosEvolucion, modContagio
      vaciarSistema( org1 );
    }
  }
  return 0;
}

void sistemaRadioProbabilidad(Organizador & organizador, double radioContagio, double probabilidadContagio ){
  for ( auto * cuarto : organizador.vectorCuartos ){
    cuarto->setRadioContagio( radioContagio );
    for (auto * persona : cuarto->personasEnElCuarto ){
      persona->setProbabilidadContagio(probabilidadContagio);
    }
  }
}


void vaciarSistema(Organizador & organizador){
  for ( auto * cuarto : organizador.vectorCuartos){
    delete cuarto;
  }
  organizador.vectorCuartos.clear();

  for ( auto * persona : organizador.vectorIndividuos){
    delete persona;
  }
  organizador.vectorIndividuos.clear();
}
