#include <iostream>
#include <cmath>
#include <vector>
#include "mpi.h"
#include "Cuarto.h"
#include "Individuo.h"
#include "Organizador.h"

void sistemaRadioProbabilidad(Organizador & organizador, double radioContagio, double probabilidadContagio);
void vaciarSistema(Organizador & organizador );

int main(void){
  double dt = 0.01;
  double dRadio = 0.1;
  double dProb = 0.05;
  int JMAX = 2;
  int IMAX = 10;
  Organizador org1;

  int pid, np;
  MPI_Init(NULL, NULL);
  MPI_Comm_rank(MPI_COMM_WORLD, &pid);
  MPI_Comm_size(MPI_COMM_WORLD, &np);

  int nLocal = 0;
  int imin = 0;
  if(IMAX%np!=0 && pid < IMAX%np ){
    nLocal = (IMAX/np)+1;
    imin = pid*nLocal;
  } else {
    nLocal = IMAX/np;
    imin = IMAX%np*(nLocal +1)+(pid-IMAX%np)*nLocal;
  }


  for( int ii = imin; ii < imin+nLocal; ii++ ){
    double radio = 1.0 + ( ii * dRadio );
    for( int jj = 0; jj < JMAX; jj++ ){
      double probabilidad = 0.08 + ( jj * dProb );
      org1.InicializarPorDefecto(1000,6,1); //Individuos, infectados
      org1.InicializarPosiciones(499.5);
      for ( auto * cuarto : org1.vectorCuartos ){
        cuarto->setDimensionCuartoX( 500.51 );
        cuarto->setDimensionCuartoY( 500.36 );
      }
      std::cout << "No Individuos:  " << org1.vectorIndividuos.size() << std::endl;
      
      org1.InicializarPosiciones(22.5);
      sistemaRadioProbabilidad(org1, radio, probabilidad);
      org1.EmpezarEvolucion(dt, 30, 200, 2 , true, probabilidad, radio); //dt, pasosContagio, pasosEvolucion, modContagio
      vaciarSistema( org1 );
    }
  }
  MPI_Finalize();
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