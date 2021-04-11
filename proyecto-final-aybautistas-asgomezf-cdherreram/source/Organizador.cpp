#include "Organizador.h"

//Constructor
Organizador::Organizador(){
  nIndividuosTotal = 10;
  nCuartosNormales = 1;
  nCuartosCuarentena = 1;
  proporcionIndividuosAMover = 0.2;
}  

Organizador::Organizador (int pNIndividuosTotal,
			  int pNCuartosNormales,
			  int pNCuartosCuarentena,
			  double pProporcionIndividuosAMover){
  nIndividuosTotal = pNIndividuosTotal;
  nCuartosNormales = pNCuartosNormales;
  nCuartosCuarentena = pNCuartosCuarentena;
  proporcionIndividuosAMover = pProporcionIndividuosAMover;
}

//Destructor
Organizador::~Organizador(){
  
}

//Getter methods
int Organizador::getNIndividuosTotal ( void ){
  return nIndividuosTotal;
}

int Organizador::getNCuartosNormales ( void ){
  return nCuartosNormales;
}

int Organizador::getNCuartosCuarentena ( void ){
  return nCuartosCuarentena;
}

double Organizador::getProporcionIndividuosAMover ( ){
  return proporcionIndividuosAMover;
}

//Setter methods
void Organizador::setNIndividuosTotal ( int pNIndividuosTotal ){
  nIndividuosTotal = pNIndividuosTotal;
}

void Organizador::setNCuartosNormales ( int pNCuartosNormales ){
  nCuartosNormales = pNCuartosNormales;
}

void Organizador::setNCuartosCuarentena ( int pNCuartosCuarentena ){
  nCuartosCuarentena = pNCuartosCuarentena;
}

void Organizador::setProporcionIndividuosAMover ( double pProporcionIndividuosAMover ){
  proporcionIndividuosAMover = pProporcionIndividuosAMover;
}

//Methods
void Organizador::EmpezarEvolucion( double dt , int pasosContagio, int pasosEvolucionPosicion, int modContagio ,
				    bool incluirAislamiento , double pProbabilidad, double pRadio ){
  for ( auto * cuarto : vectorCuartos){
    cuarto->CalcularFuerzas();
    cuarto->Start_timeintegration(dt);
  }
  
  for ( int ii = 0; ii < pasosContagio; ii++){
    for (int step = 0; step < pasosEvolucionPosicion; ++step) {
      double tstep = step*dt;
     
      for(auto * cuarto : vectorCuartos ){
        //ImprimirDinamica(tstep, pProbabilidad); 
      	cuarto->Timestep(dt); // actualiza r y v -> actualizar f
      	cuarto->CalcularFuerzas(); // actualizar la fuerza
      }
      //Aquí va la impresion
      ImprimirDinamica(tstep, pProbabilidad); 
    }
    int susceptiblesTotal = 0;
    int infectadosTotal = 0;
    int removidosTotal = 0;
    for( auto * cuarto : vectorCuartos){
      if( cuarto->getStatusCuarto() == NORMAL){
      	cuarto->CalcularContagio();
      	cuarto->ConteoIndividuosPorStatus();
      	if ( ii%modContagio == 0 && incluirAislamiento == true ){
      	  int numIndividuosAMover = cuarto->CalcularNumeroDeIndividuosAMover(getProporcionIndividuosAMover( ));
      	  for ( int kk = 0; kk < numIndividuosAMover; kk++){
      	    int idAMover = cuarto->IndividuoAMover(kk);
      	    bool cambio = CambiarIndividuoContagiado(idAMover);
          }
        }
      }
      for ( auto * persona : cuarto->personasEnElCuarto){
	if ( persona->getStatus() == INFECTADO){
	  persona->setTiempoEnfermo (persona->getTiempoEnfermo( ) +1);
	  persona->CambioStatusPorRecuperacion( );
	}
      }
      cuarto->ConteoIndividuosPorStatus();
      if ( cuarto->getStatusCuarto() == NORMAL){
	susceptiblesTotal += cuarto->getNSusceptibles();
	infectadosTotal += cuarto->getNInfectados();
	removidosTotal += cuarto->getNRemovidos();
      }
    }
    int numCuartos = vectorCuartos.size() - 1 ;
    int numIndividuos = vectorIndividuos.size();
    ImprimirDatosContagio(ii, susceptiblesTotal, infectadosTotal, removidosTotal,
			  numCuartos, numIndividuos, pProbabilidad, pRadio, incluirAislamiento);
    //std::cout << ii << "\t" << susceptiblesTotal << "\t" << infectadosTotal << "\t" << removidosTotal << "\n";
  }
}

/*void Organizador::AgregarIndividuosAlCuarto(Cuarto * pCuarto){
  for( auto * persona: vectorIndividuos ){
    bool recibe = pCuarto->RecibirIndividuos(persona);
  }
  pCuarto->ConteoIndividuosPorStatus();
  }*/

void Organizador::AgregarIndividuosAlCuarto( void ){
  int SEED = 10;
  int posicion = -1;
  std::mt19937 gen(SEED);
  std::uniform_int_distribution<int> llenado( 1, vectorCuartos.size( ) - 1 );
  
  for ( auto * persona : vectorIndividuos ){
    posicion = llenado(gen);
    vectorCuartos[posicion]->RecibirIndividuos(persona);
  }
}

void Organizador::InicializarPosiciones( double pDimensionCuarto ){
  int SEED = 3;
  std::mt19937 gen(SEED);
  std::uniform_real_distribution<double> masa(0.3, 0.5);
  std::uniform_real_distribution<double> radios(0.34, 0.36);
  // Cuidado con el tamaño del cuarto
  std::uniform_real_distribution<double> pos(1.02, pDimensionCuarto-3);
  std::uniform_real_distribution<double> vel(0.5, 0.52);
  
 #pragma omp parallel for
  for ( int ii = 0; ii < vectorIndividuos.size(); ii++){
    vectorIndividuos[ii]->setMasaIndividuo(masa(gen));
    vectorIndividuos[ii]->setDimensionIndividuo(radios(gen));
    vectorIndividuos[ii]->setPosicionX( pos(gen) );
    vectorIndividuos[ii]->setPosicionY( pos(gen) );
    vectorIndividuos[ii]->setVelocidadX( vel(gen) );
    vectorIndividuos[ii]->setVelocidadY( vel(gen) );
  }
}

bool Organizador::CambiarCuartoIndividuo( int nIndividuo, int idCuarto ){
  bool huboCambioDeCuarto = false;
  bool loQuito = false;
  bool loPuso = false;
  int nCuartoIndividuo = vectorIndividuos[nIndividuo]->getNCuarto( ); //Reporta el cuarto en donde está

  if(nCuartoIndividuo != idCuarto ){
    Individuo * individuoACambiar = vectorIndividuos[nIndividuo];
    loQuito = vectorCuartos[nCuartoIndividuo]->QuitarIndividuos(individuoACambiar);
    loPuso = vectorCuartos[idCuarto]->RecibirIndividuos(individuoACambiar);
    if ( loQuito && loPuso) huboCambioDeCuarto = true;
  }
  return huboCambioDeCuarto;
}

/*bool Organizador::CambiarIndividuoContagiado( int nIndividuo ){
  bool huboCambioDeCuarto = false;
  for ( int ii = 0; ii < vectorCuartos.size( ); ++ii){
  if(vectorCuartos[ii]->getStatusCuarto( ) == CUARENTENA){
  huboCambioDeCuarto = CambiarCuartoIndividuo( nIndividuo, ii); 
  }
  }
  return huboCambioDeCuarto;
  }*/

bool Organizador::CambiarIndividuoContagiado( int nIndividuo ){
  bool huboCambioDeCuarto = false;
  huboCambioDeCuarto = CambiarCuartoIndividuo ( nIndividuo, 0);
  return huboCambioDeCuarto;
}

/*void Organizador::FillVector(int pNIndividuosTotal){
  setNIndividuosTotal ( pNIndividuosTotal);
  int SEED = 1;
  std::mt19937 gen(SEED);
  std::uniform_int_distribution<int> dis(0,1);
  
  for(int ii = 1; ii < pNIndividuosTotal; ++ii){
    int st = dis(gen);
    Individuo * newpIndividuo = new Individuo(st, ii);
    vectorIndividuos.push_back(newpIndividuo);
  }
  }*/

void Organizador::InicializarPorDefecto( int pNIndividuosTotal , int pInfectados , int pNumCuartos ){
  int pSusceptibles = pNIndividuosTotal - pInfectados;
  setNIndividuosTotal ( pNIndividuosTotal );
  
  for ( int ii = 0; ii < pInfectados; ii++){
    Individuo * newIndividuoInfectado = new Individuo(INFECTADO, ii);
    vectorIndividuos.push_back(newIndividuoInfectado);
  }
  
  #pragma omp parallel
  {
  std::vector<Individuo*> vec_private;
  #pragma omp for nowait
    for(int ii = pInfectados; ii < getNIndividuosTotal() ; ++ii){
      Individuo * newIndividuoNormal = new Individuo;
      newIndividuoNormal->setStatus(SUSCEPTIBLE);
      vec_private.push_back(newIndividuoNormal);
    }
   
    #pragma omp critical
    vectorIndividuos.insert(vectorIndividuos.end(), vec_private.begin(), vec_private.end());
    
  }
  
  for(int jj = pInfectados; jj < getNIndividuosTotal(); ++jj){
    vectorIndividuos[jj]->setNIndividuo(jj);
  }
  
  //Crea el cuarto cuarentena del sistema
  Cuarto * CuartoCuarentena = new Cuarto(nIndividuosTotal, 0);
  CuartoCuarentena->setStatusCuarto(CUARENTENA);
  CuartoCuarentena->setCapacidad( nIndividuosTotal);
  vectorCuartos.push_back(CuartoCuarentena);

  //Crea los cuartos normales
  for ( int ii = 0; ii < pNumCuartos; ++ii){
    Cuarto * CuartoNormal = new Cuarto(nIndividuosTotal, ii + 1);
    //CuartoCuarentena->setStatusCuarto(NORMAL);
    CuartoNormal->setCapacidad( nIndividuosTotal);
    vectorCuartos.push_back(CuartoNormal);
  }
  
  AgregarIndividuosAlCuarto();
}

int Organizador::BuscarIndividuo ( int pIdIndividuo ) {
  int encontro = -1;
  for( int ii = 0; ii < vectorIndividuos.size( ); ++ii ){
    Individuo * individuoSistema = vectorIndividuos[ii];
    if( individuoSistema->getNIndividuo( ) == pIdIndividuo ){
      encontro = ii;
    }
  }
  return encontro;
}

void Organizador::ImprimirDinamica ( double tstep , double pProbabilidad ){
  std::ofstream fout;
  fout.precision(15); fout.setf(std::ios::scientific);
  fout.open("datosProbabilidad_"+std::to_string(pProbabilidad)+".txt", std::ios_base::app);
  
  for ( int ii = 0; ii < vectorIndividuos.size( ); ++ii){
    fout << vectorIndividuos[ii]->getNCuarto() << "\t"
	 << vectorIndividuos[ii]->getStatus() << "\t"
	 << vectorIndividuos[ii]->getPosicionIndividuo()[0] << "\t"
	 << vectorIndividuos[ii]->getPosicionIndividuo()[1] << "\t\t";   
  }
  fout << "\n";
  fout.close();
}

void Organizador::ImprimirDatosContagio ( int paso, int pSusceptibles, int pInfectados, int pRemovidos, int numCuartos,
					  int numIndividuos, double pProbabilidad, double pRadio , bool aislamiento ){
  std::filesystem::create_directory("datosContagio");
  int precisionVal = 2;
  std::string trimmedProb = std::to_string(pProbabilidad).substr(0, std::to_string(pProbabilidad).find(".") + precisionVal + 1);
  std::string trimmedRad = std::to_string(pRadio).substr(0, std::to_string(pRadio).find(".") + precisionVal + 1);
  std::string dname = "datosContagio/C" + std::to_string(numCuartos) + "_I" + std::to_string(numIndividuos);
  std::filesystem::create_directory(dname);
  std::string fname = dname + "/sirProb" + trimmedProb + "_Radio" + trimmedRad + ".txt";
  std::ifstream fin;
  fin.open(fname);
  if ( fin.fail()){
    std::ofstream fout;
    fout.open(fname, std::ios_base::out | std::ios_base::trunc);
    fout << "#Se genera un archivo .txt con los datos obtenidos con las simulaciones de un sistema con "  +
      std::to_string(numCuartos) + " cuarto(s) y " + std::to_string(numIndividuos) + " individuo(s)\n";
    fout << "#Se tiene un sistema con probabilidad " + std::to_string(pProbabilidad) + " y radio " + std::to_string(pRadio) + ".\n";
    if (aislamiento) fout << "#En este caso hay aislamiento\n";
    else fout << "#En este caso NO hay aislamiento\n";
    fout << paso << "\t" << pSusceptibles << "\t" << pInfectados << "\t" << pRemovidos << "\n";
  }
  else {
    std::ofstream fout;
    if (aislamiento) fout << "En este caso hay aislamiento\n";
    else fout << "#En este caso NO hay aislamiento\n";
    fout << "#En este caso hay aislamiento\n";
    fout.open(fname, std::ios_base::app);
    fout << paso << "\t" << pSusceptibles << "\t" << pInfectados << "\t" << pRemovidos << "\n";
  }
  //fout << paso << "\t" << pSusceptibles << "\t" << pInfectados << "\t" << pRemovidos << "\n";
}
