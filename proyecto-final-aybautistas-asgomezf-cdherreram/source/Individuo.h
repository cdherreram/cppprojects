#ifndef INDIVIDUO_H
#define INDIVIDUO_H

#include<iostream>
#include<vector>
#include<cmath>

const int SUSCEPTIBLE = 0;
const int INFECTADO = 1;
const int REMOVIDO = 2;
const int TIEMPORECUPERACION = 5;

class Individuo {
  
 private:
  int status;
  int tiempoEnfermo;
  double probabilidadContagio;
  double dimensionIndividuo;
  double masaIndividuo;
  int nIndividuo;
  int nCuarto;
  std::vector<double> posicionIndividuo;
  std::vector<double> velocidadIndividuo;
  std::vector<double> fuerzaIndividuo;
  
 public:
  //default constructor
  Individuo();
  
  //overload constructor
  Individuo(int ,int , double, 
	    double, double, int, int, 
	    std::vector<double>, std::vector <double>,
	    std::vector <double>);

  Individuo(int, int);
  
  //destructor
  ~Individuo();
  
  
  //Accesor functions
  int getStatus();
  //getStatus
  //@return int-status --> 0-Susceptible, 1- Infectado, 2-Removido
  
  int getTiempoEnfermo();
  //getTiempoRecuperacion
  //@return int- tiempo de recuperacion
  
  double getProbabilidadContagio();
  //getProbabilidadContagio
  //@return double- probabilidad de contagio
  
  double getDimensionIndividuo();
  //getDimensionIndividuo
  //@return double- dimension del individuo (radio)
  
  double getMasaIndividuo();
  //getMasaIndividuo
  //@return double- masa del individuo
  
  int getNIndividuo();
  //getNIndividuo
  //@return char- id del individuo
  
  int getNCuarto();
  //getNCuarto
  //@return char- id cuarto en el que esta el individuo
  
  std::vector<double> getPosicionIndividuo();
  //getPosicionIndividuo
  //@return vector- coordenadas x, y de la posicion del individuo
  
  std::vector<double> getVelocidadIndividuo();
  //getVelocidadIndividuo
  //@return vector- coordenadas x, y velocidad del individuo
  
  std::vector<double> getFuerzaIndividuo();
  //getFuerzaIndividuo
  //@return vector- coordenadas x, y fuerza individuo
  
  //Mutator functions
  void setStatus(int);
  void setTiempoEnfermo(int);
  void setProbabilidadContagio(double);
  void setDimensionIndividuo(double);
  void setMasaIndividuo(double);
  void setNIndividuo(int);
  void setNCuarto(int);
  void setPosicionIndividuo(std::vector<double>);
  void setVelocidadIndividuo(std::vector<double>);
  void setFuerzaIndividuo(std::vector<double>);
  void setPosicionX(double x);
  void setPosicionY(double y);
  void setVelocidadX(double vx);
  void setVelocidadY(double vy);
  void setFuerzaX(double fx);
  void setFuerzaY(double fy);
  //Methods
  
  void CambioStatusPorRecuperacion(); 
  bool EsVecino ( double, double, double ); 
  
};

#endif
