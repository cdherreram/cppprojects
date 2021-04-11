#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

#include "Organizador.h"
#include "Cuarto.h"
#include "Individuo.h"

TEST_CASE("Probabilidad cero sin aislamiento con un infectado"){
  Organizador organizadorPorDefecto;
  double dt = 0.01;
  organizadorPorDefecto.InicializarPorDefecto(20,1,1);
  organizadorPorDefecto.InicializarPosiciones(7.2);
  for( auto * cuarto : organizadorPorDefecto.vectorCuartos ){
    cuarto->setDimensionCuartoX(7.21);
    cuarto->setDimensionCuartoX(6.59);
    cuarto->ConteoIndividuosPorStatus();
  }

  REQUIRE(organizadorPorDefecto.vectorCuartos.size() == 2);
  REQUIRE(organizadorPorDefecto.vectorCuartos[0]->getNSusceptibles() == 0);
  REQUIRE(organizadorPorDefecto.vectorCuartos[0]->getNInfectados() == 0);
  REQUIRE(organizadorPorDefecto.vectorCuartos[1]->getNSusceptibles() == 19);
  REQUIRE(organizadorPorDefecto.vectorCuartos[1]->getNInfectados() == 1);

  for ( auto * cuarto : organizadorPorDefecto.vectorCuartos){
    for( auto * persona : cuarto->personasEnElCuarto){
      persona->setProbabilidadContagio(0);
    }
  }
  organizadorPorDefecto.EmpezarEvolucion(dt, 15, 40, 1, false, 0, 1.5);
  REQUIRE(organizadorPorDefecto.vectorCuartos[0]->getNSusceptibles() == 0);
  REQUIRE(organizadorPorDefecto.vectorCuartos[0]->getNInfectados() == 0);
  REQUIRE(organizadorPorDefecto.vectorCuartos[1]->getNSusceptibles() == 19);
  REQUIRE(organizadorPorDefecto.vectorCuartos[1]->getNRemovidos() == 1);
  REQUIRE(organizadorPorDefecto.vectorCuartos[1]->getNInfectados() == 0);
}

TEST_CASE("Probabilidad cero con aislamiento con un infectado"){
  Organizador organizadorPorDefecto;
  double dt = 0.01;
  organizadorPorDefecto.InicializarPorDefecto(20,1,1);
  organizadorPorDefecto.InicializarPosiciones(7.2);
  for( auto * cuarto : organizadorPorDefecto.vectorCuartos ){
    cuarto->setDimensionCuartoX(7.21);
    cuarto->setDimensionCuartoX(6.59);
    cuarto->ConteoIndividuosPorStatus();
  }

  REQUIRE(organizadorPorDefecto.vectorCuartos.size() == 2);
  REQUIRE(organizadorPorDefecto.vectorCuartos[0]->getNSusceptibles() == 0);
  REQUIRE(organizadorPorDefecto.vectorCuartos[0]->getNInfectados() == 0);
  REQUIRE(organizadorPorDefecto.vectorCuartos[1]->getNSusceptibles() == 19);
  REQUIRE(organizadorPorDefecto.vectorCuartos[1]->getNInfectados() == 1);

  for ( auto * cuarto : organizadorPorDefecto.vectorCuartos){
    for( auto * persona : cuarto->personasEnElCuarto){
      persona->setProbabilidadContagio(0);
    }
  }
  organizadorPorDefecto.EmpezarEvolucion(dt, 15, 40, 1, true, 0, 1.5);
  REQUIRE(organizadorPorDefecto.vectorCuartos[0]->getNSusceptibles() == 0);
  REQUIRE(organizadorPorDefecto.vectorCuartos[0]->getNInfectados() == 0);
  REQUIRE(organizadorPorDefecto.vectorCuartos[1]->getNSusceptibles() == 19);
  REQUIRE(organizadorPorDefecto.vectorCuartos[1]->getNRemovidos() == 1);
  REQUIRE(organizadorPorDefecto.vectorCuartos[1]->getNInfectados() == 0);
}

TEST_CASE("Probabilidad uno sin aislamiento con un infectado"){
  Organizador organizadorPorDefecto;
  double dt = 0.01;
  organizadorPorDefecto.InicializarPorDefecto(20,1,1);
  organizadorPorDefecto.InicializarPosiciones(7.2);
  for( auto * cuarto : organizadorPorDefecto.vectorCuartos ){
    cuarto->setDimensionCuartoX(7.21);
    cuarto->setDimensionCuartoX(6.59);
    cuarto->ConteoIndividuosPorStatus();
  }

  REQUIRE(organizadorPorDefecto.vectorCuartos.size() == 2);
  REQUIRE(organizadorPorDefecto.vectorCuartos[0]->getNSusceptibles() == 0);
  REQUIRE(organizadorPorDefecto.vectorCuartos[0]->getNInfectados() == 0);
  REQUIRE(organizadorPorDefecto.vectorCuartos[1]->getNSusceptibles() == 19);
  REQUIRE(organizadorPorDefecto.vectorCuartos[1]->getNInfectados() == 1);

  for ( auto * cuarto : organizadorPorDefecto.vectorCuartos){
    for( auto * persona : cuarto->personasEnElCuarto){
      persona->setProbabilidadContagio(1);
    }
  }
  organizadorPorDefecto.EmpezarEvolucion(dt, 15, 40, 1, false, 1, 1.5);
  REQUIRE(organizadorPorDefecto.vectorCuartos[0]->getNSusceptibles() == 0);
  REQUIRE(organizadorPorDefecto.vectorCuartos[0]->getNInfectados() == 0);
  REQUIRE(organizadorPorDefecto.vectorCuartos[1]->getNSusceptibles() == 0);
  REQUIRE(organizadorPorDefecto.vectorCuartos[1]->getNRemovidos() == 20);
  REQUIRE(organizadorPorDefecto.vectorCuartos[1]->getNInfectados() == 0);
}

TEST_CASE("Probabilidad cero sin aislamiento con 50% de infectados"){
  Organizador organizadorPorDefecto;
  double dt = 0.01;
  organizadorPorDefecto.InicializarPorDefecto(20,10,1);
  organizadorPorDefecto.InicializarPosiciones(7.2);
  for( auto * cuarto : organizadorPorDefecto.vectorCuartos ){
    cuarto->setDimensionCuartoX(7.21);
    cuarto->setDimensionCuartoX(6.59);
    cuarto->ConteoIndividuosPorStatus();
  }

  REQUIRE(organizadorPorDefecto.vectorCuartos.size() == 2);
  REQUIRE(organizadorPorDefecto.vectorCuartos[0]->getNSusceptibles() == 0);
  REQUIRE(organizadorPorDefecto.vectorCuartos[0]->getNInfectados() == 0);
  REQUIRE(organizadorPorDefecto.vectorCuartos[1]->getNSusceptibles() == 10);
  REQUIRE(organizadorPorDefecto.vectorCuartos[1]->getNInfectados() == 10);

  for ( auto * cuarto : organizadorPorDefecto.vectorCuartos){
    for( auto * persona : cuarto->personasEnElCuarto){
      persona->setProbabilidadContagio(0);
    }
  }
  organizadorPorDefecto.EmpezarEvolucion(dt, 15, 40, 1, false, 0, 1.5);
  REQUIRE(organizadorPorDefecto.vectorCuartos[0]->getNSusceptibles() == 0);
  REQUIRE(organizadorPorDefecto.vectorCuartos[0]->getNInfectados() == 0);
  REQUIRE(organizadorPorDefecto.vectorCuartos[1]->getNSusceptibles() == 10);
  REQUIRE(organizadorPorDefecto.vectorCuartos[1]->getNRemovidos() == 10);
  REQUIRE(organizadorPorDefecto.vectorCuartos[1]->getNInfectados() == 0);
}
