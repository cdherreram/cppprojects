#include "clusters.h"

//Función recursiva que determina los clusters con un id que inicia desde 2
//Preview: La matriz ya esta inicializada como matriz de 1's y 0's
//Param: Matriz (como puntero)
//       Indices i,j de la matriz
//       id Cluster en el que va la recursion
//       tamanho local del cluster generado
//       booleanos con informacion de posible cluster percolante
//Return: Si la entrada es inicio de un cluster, retorna 1. De lo contrario, retorna 0.
int clusters (Eigen::MatrixXd & m, int i, int j, int idCluster, int & tamClusterLocal,
	      bool & inicio_i, bool & inicio_j, bool & final_i, bool & final_j){
  int tmp  = 0;
  if ( m(i,j) == 1 ){
    
    m( i, j ) = idCluster;
    tamClusterLocal += 1;

    //Entró en un posible cluster percolante
    if ( i == 0 ) inicio_i = true; //En la primera fila
    if ( j == 0 ) inicio_j = true; //En la primera columna
    if( j == m.cols()-1 ) final_j = true; //En la ultima columna
    if( i == m.cols()-1 ) final_i = true; //En la ultima fila

    //Proceso recursivo
    if ( j+1 < m.cols() ) clusters( m, i, j+1, idCluster, tamClusterLocal, inicio_i, inicio_j, final_i, final_j); //derecha
    if ( i+1 < m.rows() ) clusters( m, i+1, j, idCluster,tamClusterLocal, inicio_i, inicio_j, final_i, final_j); //abajo
    if ( j-1 >= 0 ) clusters( m, i, j-1, idCluster,tamClusterLocal, inicio_i, inicio_j, final_i, final_j); //izquierda
    if ( i-1 >= 0 )  clusters( m, i-1, j, idCluster,tamClusterLocal, inicio_i, inicio_j, final_i, final_j); //arriba
    return 1;
  }
  else return tmp;
}
