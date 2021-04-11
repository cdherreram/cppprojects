#include "percolacion.h"

//Funcion que identifica los clusteres en la matriz y calcula el cluster percolante mas grande
//Param: Matriz (como puntero)
//Return: tamanho del cluster percolante mas grande
int percolacion (Eigen::MatrixXd & m){
  int idClusterPercolante = 0;
  int tamMatrizPercolanteMasGrande = 0;
  int tamClusterLocal = 0;
  int idCluster = 2;
  int conteoTamMatriz = 0;
  int l = m.cols();

  bool percola = false;
  bool inicio_i = false;
  bool inicio_j = false;
  bool final_i = false;
  bool final_j = false;
  
  for( int i = 0; i < l; i++ ){
    for( int j = 0; j < l; j++ ){
      if ( i != 0 && j != 0 ){
	inicio_i = false;
	inicio_j = false;
	final_i = false;
	final_j = false;
	percola = false;
      }
      conteoTamMatriz = clusters(m,i,j,idCluster,tamClusterLocal,
				 inicio_i, inicio_j, final_i, final_j);
      if ( conteoTamMatriz == 1 ){
	if( inicio_i && final_i ) percola = true;
	if( inicio_j && final_j ) percola = true;
	if( tamClusterLocal > tamMatrizPercolanteMasGrande && percola == true ){
	  tamMatrizPercolanteMasGrande = tamClusterLocal;
	  idClusterPercolante = idCluster;
	}
	tamClusterLocal = 0;
      }
      idCluster += conteoTamMatriz;
      inicio_i = false;
      inicio_j = false;
      final_i = false;
      final_j = false;
      percola = false;
    }
  }
  return tamMatrizPercolanteMasGrande;
}
