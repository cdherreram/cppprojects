#ifndef ORGANIZADOR_H
#define ORGANIZADOR_H

#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <filesystem>
#include <string>
#include <omp.h>
#include "Cuarto.h"
#include "Individuo.h"

class Organizador {
  
  //Atributos
 private:
  int nIndividuosTotal;
  int nCuartosNormales;
  int nCuartosCuarentena;
  double proporcionIndividuosAMover;
  
 public:
  std::vector <Individuo*> vectorIndividuos;
  std::vector <Cuarto*> vectorCuartos;
  
  //Constructor
  Organizador ( ); //Constructor por defecto
  Organizador ( int, int, int, double );
  
  //Destructor
  ~Organizador ( );
  
  //Getter methods
  int getNIndividuosTotal ( );
  //getNIndividuosTotal
  //@return int - numero total de individuos
  int getNCuartosNormales ( );
  //getNCuartosNormales
  //@return int - numero total de cuartos normales
  int getNCuartosCuarentena ( );
  //getNCuartosCuarentena
  //@return int - numero total de cuartos en cuarentena
  double getProporcionIndividuosAMover ( );
  //getProporcionINdividuosAMover
  //@return double - proporcion de individuos a mover
  
  //Setter methods
  void setNIndividuosTotal ( int );
  void setNCuartosNormales ( int );
  void setNCuartosCuarentena ( int );
  void setProporcionIndividuosAMover ( double );
  
  //Methods
  void InicializarPosiciones( double );
  void EmpezarEvolucion( double , int, int, int, bool, double , double);  
  bool CambiarCuartoIndividuo( int , int );
  bool CambiarIndividuoContagiado( int );
  void FillVector( int );
  void InicializarPorDefecto( int , int , int);
  int BuscarIndividuo ( int );
  void AgregarIndividuosAlCuarto( void );
  void ImprimirDinamica( double , double );
  void ImprimirDatosContagio ( int, int, int, int, int, int, double, double , bool);

};

#endif
