#ifndef CUARTO_H
#define CUARTO_H

#include <iostream>
#include <vector>
#include <random>
#include <omp.h>
#include "Individuo.h"

const int CUARENTENA = 0;
const int NORMAL = 1;
const int DIMENSION = 2;

class Cuarto {

  //Atributos
  int capacidad;
  int nInfectados;
  int nSusceptibles;
  int nRemovidos;
  int statusCuarto;
  int idCuarto;
  double radioContagio;
  double tasaInmigracion;
  double dimensionCuarto[DIMENSION];
  
 public:
  std::vector<Individuo*> personasEnElCuarto;

  //Constructor
  Cuarto ( ); //Constructor por defecto
  Cuarto ( int, int );
  Cuarto ( int, int, int, int , int, int, double, double, double * );

  //Destructor
  ~Cuarto ( );
  
  //Getter methods
  int getCapacidad ( );
     //getCapacidad
     //@return int - capacidad del cuarto
  int getNInfectados ( );
     //getNInfectados
     //@return int - numero de infectados en el cuarto
  int getNSusceptibles ( );
     //getNSusceptibles
     //@return int - numero de susceptibles en el cuarto
  int getNRemovidos ( );
     //getNRemovidos
     //@return int - numero de removidos en el cuarto
  int getStatusCuarto ( );
     //getStatusCuarto
     //@return int - status del cuarto (NORMAL = 0; CUARENTENA = 1)
  int getIdCuarto ( );
     //getIdCuarto
     //@return int - id del cuarto
  double getRadioContagio ( );
     //getRadioContagio
     //@return double - radio de contagio en el cuarto
  double getTasaInmigracion ( );
     //getTasaInmigracion
     //@return double - tasa de inmigracion
  double * getDimensionCuarto ( );
     //getDimensionCuarto
     //@return double * - dimension del cuarto en coordenadas x y y8
  std::vector<Individuo*> getPersonasEnElCuarto ( );
     //getPersonasEnElCuarto
     //@return vector - vector de personas en el cuarto

  //Setter methods
  void setCapacidad ( int );
  void setNInfectados ( int );
  void setNSusceptibles ( int );
  void setNRemovidos ( int );
  void setStatusCuarto ( int );
  void setIdCuarto ( int );
  void setRadioContagio ( double );
  void setTasaInmigracion ( double );
  void setDimensionCuartoX ( double );
  void setDimensionCuartoY ( double );
    
  //Methods
  void ConteoIndividuosPorStatus( void );
  int CalcularNumeroDeIndividuosAMover( double );
  int IndividuoAMover( int );
  int BuscarIndividuoEnCuarto ( int );
  bool RecibirIndividuos( Individuo * );
  bool QuitarIndividuos( Individuo * );
  void Timestep( double );
  void Start_timeintegration( double );
  void CalcularFuerzas( void );
  void CalcularContagio( void );
};

#endif
