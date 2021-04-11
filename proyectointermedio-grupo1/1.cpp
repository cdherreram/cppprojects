#include<iostream>
#include<cmath>
#include<random>
#include<eigen3/Eigen/Dense>
#include<fstream>
#include<vector>

void generacionMallaAleatoriaEigen(Eigen::MatrixXd & m, int semilla, double prob);
int clusters (Eigen::MatrixXd & m, int i, int j, int idCluster, int & tamClusterLocal,
	      bool & inicio_i, bool & inicio_j, bool & final_i, bool & final_j);
int percolacion ( Eigen::MatrixXd & m);
void imprimirDatos ( std::ofstream & fout, int l, double p ,
		     std::vector<double> guardaP, std::vector<double> guardaS);
Eigen::VectorXd calculoPyS (Eigen::VectorXd v , int l); // P, tamanho promedio

int main (void)
{
  int tamanho = 0;
  std::ofstream fout;
  Eigen::VectorXd v(20);
  Eigen::VectorXd datosPyS(2);
  std::vector<double> guardaP;
  std::vector<double> guardaS;
  fout.open("datos1.txt");
  fout << "#L \t\t p \t\t Pmean \t\t Pstd \t\t smean \t\t sstd" << std::endl;
  for ( int l = 32; l <= 512; l *= 2 ){
    for ( double p = 0.41; p < 0.71; p += 0.01 ){
      for( int n = 1; n < 4000; n += 50 ){
	//    1, 50, 100, 167
	for ( int i= 0; i < 20 ; i++){
	  int seed = n + i;
	  Eigen::MatrixXd m(l,l);
	  generacionMallaAleatoriaEigen( m ,seed, p);
	  tamanho = percolacion( m );
	  v( i ) = tamanho;
	}
	datosPyS = calculoPyS( v , l );
	guardaP.push_back(datosPyS(0));
	guardaS.push_back(datosPyS(1));
	v.setZero();
	datosPyS.setZero();
      }
      imprimirDatos(fout, l, p,guardaP, guardaS);
      guardaP.clear();
      guardaS.clear(); 
    }
  }
  return 0;
}

//Matriz para llenar segun la probabilidad
//Param: Matriz (como puntero)
//       Valor de semilla
//       probabilidad p
void generacionMallaAleatoriaEigen(Eigen::MatrixXd & m, int semilla, double prob){
  std::mt19937 gen(semilla);
  std::binomial_distribution<> dis(1,prob);
  for(int i = 0; i < m.cols(); i++){
    for(int j = 0; j < m.cols(); j++){
      m(i,j) = dis(gen);
    }
  }
}

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

//Funcion que imprime los datos de tamanho de matriz, probabilidad p, y tamanho del cluster percolante mas grande
//   Si la matriz no tiene cluster percolante, tamanho imprime 0.
void imprimirDatos ( std::ofstream & fout, int l, double p ,
		     std::vector<double> guardaP, std::vector<double> guardaS){

  double promedioTamanhos = 0;
  double promedioP = 0;
  double desvTamanhos = 0;
  double desvP = 0;

  //Calcula promedio Tamanhos
  for( int i = 0; i < guardaS.size( ); i++){
    promedioTamanhos += guardaS[i];
  }
  promedioTamanhos = promedioTamanhos/guardaS.size();
  
  //Calcula promedio P
  for( int i = 0; i < guardaP.size( ); i++){
    promedioP += guardaP[i];
  }
  promedioP = promedioP/guardaP.size();

  //Calcula desviaciones Tamanhos
  for( int i = 0; i < guardaS.size( ); i++){
    desvTamanhos += std::pow(guardaS[i]-promedioTamanhos,2);
  }
  desvTamanhos = std::sqrt(desvTamanhos/guardaS.size());

  //Calcula desviaciones P
  for( int i = 0; i < guardaP.size( ); i++){
    desvP += std::pow(guardaP[i]-promedioP,2);
  }
  desvP = std::sqrt(desvP/guardaP.size());

  fout.precision(4); fout.setf(std::ios::scientific);
  //Eigen::VectorXd impresion(guardaS.size());
  //for (int b= 0; b < guardaS.size();b++) impresion(b) = guardaS[b];
  fout << l << "\t\t" << p << "\t\t" << promedioP << "\t\t" <<desvP  << "\t\t" << promedioTamanhos  << "\t\t" << desvTamanhos << std::endl;
}

Eigen::VectorXd calculoPyS ( Eigen::VectorXd v , int l){
  int conteo = 0;
  double suma = 0;
  Eigen::VectorXd salida(2);
  salida.setZero();
  for ( int i = 0; i < v.size(); i++){
    if ( v(i) != 0 ) conteo++;
  }
  salida(0) = conteo*1.0 / v.size(); //P
  suma = v.sum();
  if ( conteo != 0 ) salida(1) = suma*1.0 / (conteo*l*l); //Promedio tamanhos
  return salida;
}

