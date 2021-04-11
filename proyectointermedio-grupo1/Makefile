CXX=g++
CXXFLAGS=-fsanitize=address -fsanitize=undefined
all: main.x datos1.txt P.pdf s.pdf

main.x: main.o generacionMallaAleatoria.o clusters.o percolacion.o imprimirDatos.o calculoPyS.o
	$(CXX) $(CXXFLAGS) $^ -o $@ -O2

%.o: %.cpp
		g++ -c $<

datos1.txt: main.x
	./$^

%.pdf : %.gp datos1.txt
		gnuplot	$<

test: test_percolacion.x

test_percolacion.x: generacionMallaAleatoria.o  percolacion.o clusters.o percolacion_test.cpp
	g++ $^ -o $@

.PHONY: clean
clean:
		rm -f *.x *.o datos1.txt P.pdf s.pdf *.out *~
