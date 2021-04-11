#include "Individuo.h"

//Constructor
Individuo::Individuo(){
  status = SUSCEPTIBLE;
  tiempoEnfermo = 0;
  masaIndividuo = 0.3;
  probabilidadContagio = 0.1;
  dimensionIndividuo = 0.2;
  nIndividuo = 1;
  nCuarto = 1;
  posicionIndividuo = {0.5,0.5};
  velocidadIndividuo = {0.5,0.5};
  fuerzaIndividuo = {0.5,0.5};
}

Individuo::Individuo(int pStatus, int pNIndividuo){
  status = pStatus;
  tiempoEnfermo = 0;
  probabilidadContagio = 0.3;
  dimensionIndividuo = 0.2;
  masaIndividuo = 0.3;
  nIndividuo = pNIndividuo;
  nCuarto = 1;
  posicionIndividuo = {0.5,0.5};
  velocidadIndividuo = {0.5,0.5};
  fuerzaIndividuo = {0.5,0.5};
}

Individuo::Individuo(int pStatus, int pTiempoEnfermo, double pProbabilidadContagio, 
		     double pDimensionIndividuo, double pMasaIndividuo, int pNIndividuo, int pNCuarto, 
		     std::vector<double> pPosicionIndividuo, std::vector <double> pVelocidadIndividuo,
		     std::vector <double> pFuerzaIndividuo){
  
  status = pStatus;
  tiempoEnfermo = pTiempoEnfermo;
  probabilidadContagio = pProbabilidadContagio;
  dimensionIndividuo = pDimensionIndividuo;
  masaIndividuo = pMasaIndividuo;
  nIndividuo = pNIndividuo;
  nCuarto = pNCuarto;
  posicionIndividuo[0] = pPosicionIndividuo[0];
  posicionIndividuo[1] = pPosicionIndividuo[1];
  velocidadIndividuo[0] = pVelocidadIndividuo[0];
  velocidadIndividuo[1] = pVelocidadIndividuo[1];
  fuerzaIndividuo[0] = pFuerzaIndividuo[0];
  fuerzaIndividuo[1] = pFuerzaIndividuo[1];
}

//Destructor
Individuo::~Individuo(){

}

//Accesor functions

int Individuo::getStatus(){
  return status;
}

int Individuo::getTiempoEnfermo(){
  return tiempoEnfermo;
}

double Individuo::getProbabilidadContagio(){
  return probabilidadContagio;
}

double Individuo::getDimensionIndividuo(){
  return dimensionIndividuo;
}

double Individuo::getMasaIndividuo(){
  return masaIndividuo;
}

int Individuo::getNIndividuo(){
  return nIndividuo;
}

int Individuo::getNCuarto(){
  return nCuarto;
}

std::vector<double> Individuo::getPosicionIndividuo(){
  return posicionIndividuo;
}

std::vector<double> Individuo::getVelocidadIndividuo(){
  return velocidadIndividuo;
}

std::vector<double> Individuo::getFuerzaIndividuo(){
  return fuerzaIndividuo;
}

// Mutator functions
void Individuo::setStatus(int pStatus){
  status = pStatus;
}

void Individuo::setTiempoEnfermo(int pTiempoEnfermo){
  tiempoEnfermo = pTiempoEnfermo;
}

void Individuo::setProbabilidadContagio(double pProbabilidadContagio){
  probabilidadContagio = pProbabilidadContagio;
}

void Individuo::setDimensionIndividuo(double pDimensionIndividuo){
  dimensionIndividuo = pDimensionIndividuo;
}

void Individuo::setMasaIndividuo(double pMasaIndividuo){
  masaIndividuo = pMasaIndividuo;
}

void Individuo::setNIndividuo(int pNIndividuo){
  nIndividuo = pNIndividuo;
}

void Individuo::setNCuarto(int pNCuarto){
  nCuarto = pNCuarto;
}

void Individuo::setPosicionX(double x){
  posicionIndividuo[0] = x;
}

void Individuo::setPosicionY(double y){
  posicionIndividuo[1] = y;
}


void Individuo::setVelocidadX(double vx){
  velocidadIndividuo[0] = vx;
}

void Individuo::setVelocidadY(double vy){
  velocidadIndividuo[1] = vy;
}

void Individuo::setFuerzaX(double fx){
  fuerzaIndividuo[0] = fx;
}

void Individuo::setFuerzaY(double fy){
  fuerzaIndividuo[1] = fy;
}


//Methods
void Individuo::CambioStatusPorRecuperacion( ){
  if (getStatus() == INFECTADO){
    if (getTiempoEnfermo() >= TIEMPORECUPERACION){ 
      status = REMOVIDO;
    }
  }  
}

bool Individuo::EsVecino( double x, double y, double rContagio ){
  bool esVecino = false;
  double x1 = 0.0;
  double y1 = 0.0;
  double dx = 0.0;
  double dy = 0.0;
  double distanciaSq = 0.0;
  double radioMinimo = 0.0;
    x1 = posicionIndividuo[0];
    y1 = posicionIndividuo[1];
    dx = std::fabs(x - x1);
    dy = std::fabs(y - y1);
    distanciaSq = (dx*dx) + (dy*dy);
    radioMinimo = rContagio;
    if ( distanciaSq < radioMinimo*radioMinimo ) {
      esVecino = true;
    
  }
  
  return esVecino;
}
