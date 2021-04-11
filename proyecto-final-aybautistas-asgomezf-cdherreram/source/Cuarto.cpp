#include "Cuarto.h"

//Constructor
Cuarto::Cuarto ( ){
  capacidad = 10;
  nInfectados = 0;
  nSusceptibles = capacidad - nInfectados - nRemovidos;
  nRemovidos= 0;
  statusCuarto = NORMAL;
  idCuarto = 1;
  radioContagio = 5;
  tasaInmigracion = 2;
  dimensionCuarto[0] = 7.21;
  dimensionCuarto[1] = 8.32;
}

Cuarto::Cuarto( int pCapacidad, int pIdCuarto ){
  capacidad = pCapacidad;
  nInfectados = 0;
  nSusceptibles = capacidad - nInfectados - nRemovidos;
  nRemovidos= 0;
  statusCuarto = NORMAL;
  idCuarto = pIdCuarto;
  radioContagio = 5;
  tasaInmigracion = 2;
  dimensionCuarto[0] = 7.21;
  dimensionCuarto[1] = 8.32;
}

Cuarto::Cuarto( int pCapacidad, int pNInfectados, int pNSusceptibles,
		 int pNRemovidos, int pStatusCuarto, int pIdCuarto,
		 double pRadioContagio, double pTasaInmigracion,
		double * pDimensionCuarto ){
  capacidad = pCapacidad;
  nInfectados = pNInfectados;
  nSusceptibles = pNSusceptibles;
  nRemovidos = pNRemovidos;
  statusCuarto = pStatusCuarto;
  idCuarto = pIdCuarto;
  radioContagio = pRadioContagio;
  tasaInmigracion = pTasaInmigracion;
  dimensionCuarto[0] = pDimensionCuarto[0];
  dimensionCuarto[1] = pDimensionCuarto[1];
}

//Destructor
Cuarto::~Cuarto( ){

}

//Getter Methods
int Cuarto::getCapacidad ( void) {
  return capacidad;
}

int Cuarto::getNInfectados ( void ) {
  return nInfectados;
}

int Cuarto::getNSusceptibles ( void ) {
  return nSusceptibles;
}

int Cuarto::getNRemovidos ( void  ) {
  return nRemovidos;
}

int Cuarto::getStatusCuarto ( void ) {
  return statusCuarto;
}

int Cuarto::getIdCuarto ( void ) {
  return idCuarto;
}

double Cuarto::getRadioContagio ( void ) {
  return radioContagio;
}

double Cuarto::getTasaInmigracion ( void ) {
  return tasaInmigracion;
}

double * Cuarto::getDimensionCuarto ( void ) {
  return dimensionCuarto;
}

std::vector<Individuo*> Cuarto::getPersonasEnElCuarto ( void ) {
  return personasEnElCuarto;
}

//Setter Methods
void Cuarto::setCapacidad ( int pCapacidad ) {
  capacidad = pCapacidad;
}

void Cuarto::setNInfectados ( int pNInfectados ) {
  nInfectados = pNInfectados;
}

void Cuarto::setNSusceptibles ( int pNSusceptibles ) {
  nSusceptibles = pNSusceptibles;
}

void Cuarto::setNRemovidos ( int pNRemovidos ) {
  nRemovidos = pNRemovidos;
}

void Cuarto::setStatusCuarto ( int pStatusCuarto ) {
  statusCuarto = pStatusCuarto;
}

void Cuarto::setIdCuarto ( int pIdCuarto ) {
  idCuarto = pIdCuarto;
}

void Cuarto::setRadioContagio ( double pRadioContagio ) {
  radioContagio = pRadioContagio;
}

void Cuarto::setTasaInmigracion ( double pTasaInmigracion ) {
  tasaInmigracion = pTasaInmigracion;
}

void Cuarto::setDimensionCuartoX ( double pDimensionCuartoX ) {
  dimensionCuarto[0] = pDimensionCuartoX;
}

void Cuarto::setDimensionCuartoY ( double pDimensionCuartoY ) {
  dimensionCuarto[1] = pDimensionCuartoY;
}

//Methods
void Cuarto::ConteoIndividuosPorStatus( void ){
  int conteoSusceptibles = 0;
  int conteoInfectados = 0;
  int conteoRemovidos = 0;
  for ( auto persona : getPersonasEnElCuarto( ) ){
    if ( persona-> getStatus() == SUSCEPTIBLE ){
      conteoSusceptibles += 1;
    } else if ( persona-> getStatus() == INFECTADO ) {
      conteoInfectados += 1;
    } else if ( persona-> getStatus() == REMOVIDO ) {
      conteoRemovidos += 1;
    }
  }
  setNSusceptibles( conteoSusceptibles );
  setNInfectados( conteoInfectados );
  setNRemovidos( conteoRemovidos );
}

int Cuarto::CalcularNumeroDeIndividuosAMover( double proporcionIndividuosAMover ){
  return proporcionIndividuosAMover * getNInfectados( );
}

int Cuarto::IndividuoAMover ( int seed ){
  std::mt19937 gen(seed); //declarando el generador
  int max = personasEnElCuarto.size() -1;
  std::uniform_int_distribution<int> dis(0,max);
  dis.param(std::uniform_int_distribution<int>::param_type(0,max));
  
  int idAEnviar = -1;
  bool encontro = false;
  while ( !encontro ){
    double tmp = dis(gen);
    if( personasEnElCuarto[tmp]->getStatus() == INFECTADO){
      idAEnviar = personasEnElCuarto[tmp]->getNIndividuo();
      encontro = true;
    }
  }
  return idAEnviar;
}

int Cuarto::BuscarIndividuoEnCuarto ( int pIdIndividuo ){
  int posicion = -1;
  for (int ii = 0; ii < personasEnElCuarto.size(); ++ii){
    if ( personasEnElCuarto[ii]->getNIndividuo() == pIdIndividuo){
      posicion = ii;
    }
  }
  return posicion;
}

bool Cuarto::RecibirIndividuos(Individuo * pIndividuo ){
  bool seRecibio = false;
  if ( personasEnElCuarto.size() <= getCapacidad( ) ){
    pIndividuo->setNCuarto( getIdCuarto( ) );
    personasEnElCuarto.push_back(pIndividuo);
    seRecibio = true;
  }
  return seRecibio;
}

bool Cuarto::QuitarIndividuos(Individuo * pIndividuo ){
  bool seQuito = false;
  int idIndividuoAQuitar = pIndividuo->getNIndividuo();
  int posicionEnVectorDelCuarto = BuscarIndividuoEnCuarto( idIndividuoAQuitar );
  personasEnElCuarto.erase( personasEnElCuarto.begin() + posicionEnVectorDelCuarto);
  return seQuito = true;
}

void Cuarto::Start_timeintegration( double dt ){
  for ( auto * persona : personasEnElCuarto ){
    persona->setVelocidadX( persona->getVelocidadIndividuo()[0]- (dt*persona->getFuerzaIndividuo()[0])/(2*persona->getMasaIndividuo( )));
    persona->setVelocidadY( persona->getVelocidadIndividuo()[1]- (dt*persona->getFuerzaIndividuo()[1])/(2*persona->getMasaIndividuo( )));
  }
}

void Cuarto::Timestep( double dt ){
  for( auto * persona : personasEnElCuarto ){
    persona->setVelocidadX(persona->getVelocidadIndividuo( )[0] + (persona->getFuerzaIndividuo()[0]*dt)/persona->getMasaIndividuo( ));
    persona->setVelocidadY(persona->getVelocidadIndividuo( )[1] + (persona->getFuerzaIndividuo()[1]*dt)/persona->getMasaIndividuo( ));
    persona->setPosicionX(persona->getPosicionIndividuo( )[0] + persona->getVelocidadIndividuo( )[0]*dt);
    persona->setPosicionY(persona->getPosicionIndividuo( )[1] + persona->getVelocidadIndividuo( )[1]*dt);
  }
}

void Cuarto::CalcularFuerzas( void ){  
  double K = 323.4;
  double B = 0.81;
  
  //reset forces
  for( auto * persona : personasEnElCuarto ){
    persona->setFuerzaX( 0.0 );
    persona->setFuerzaY( 0.0 );
  }
  
  for( auto * persona: personasEnElCuarto ){
    double delta = 0;
    double cambio = 0;
    
    //Fuerza de rebote con el suelo
    delta = persona->getDimensionIndividuo( )- persona->getPosicionIndividuo()[1];
    if ( delta > 0 ){
      persona->setFuerzaY(persona->getFuerzaIndividuo()[1] + K*delta
			  - B*persona->getMasaIndividuo( )*persona->getVelocidadIndividuo()[1]);
    }
    
    //Fuerza contra la pared superior
    delta = persona->getPosicionIndividuo()[1] + persona->getDimensionIndividuo( ) - getDimensionCuarto( )[1];
    if ( delta > 0 ){
    persona->setFuerzaY(persona->getFuerzaIndividuo()[1] - K*delta
			- B*persona->getMasaIndividuo( )*persona->getVelocidadIndividuo()[1]);
    }
    
    //Fuerza horizontal contra pared de la derecha
    delta = persona->getPosicionIndividuo()[0] + persona->getDimensionIndividuo( ) -getDimensionCuarto( )[0];
    if ( delta > 0 ){
      persona->setFuerzaX(persona->getFuerzaIndividuo()[0] - K*delta
			  - B*persona->getMasaIndividuo( )*persona->getVelocidadIndividuo()[0]);
    }
    
    //Fuerza horizontal contra pared de la izquierda
    delta = -(persona->getPosicionIndividuo()[0] - persona->getDimensionIndividuo( ) );
    if ( delta > 0 ){
      persona->setFuerzaX(persona->getFuerzaIndividuo()[0] +K*delta
			  - B*persona->getMasaIndividuo( )*persona->getVelocidadIndividuo()[0]);
    }
  }
}

void Cuarto::CalcularContagio( void ){
  int SEED = 1;
  std::mt19937 gen(SEED); //declarando el generador
  for ( auto * persona1 : personasEnElCuarto ){
    if (persona1->getStatus() == INFECTADO){
      std::binomial_distribution<int> dis(1,persona1->getProbabilidadContagio( ));
      for ( auto * persona2 : personasEnElCuarto ){
	double x = persona2->getPosicionIndividuo()[0];
	double y = persona2->getPosicionIndividuo()[1];
	if( persona1->EsVecino(x,y,getRadioContagio( ) )){
	  if ( persona2->getStatus() == SUSCEPTIBLE){
	    if (dis(gen)) persona2->setStatus(INFECTADO);
	    
	  }
	}
      }
    }
  }
}
