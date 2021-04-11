CXX=g++
all: main.x

main.x: main.o Individuo.o Cuarto.o Organizador.o
		$(CXX) $^ -o $@

%.o: %.cpp
		g++ -c $<


test: Organizador_test.x

Organizador_test.x: Individuo.o Cuarto.o Organizador.o Organizador_test.cpp
	g++ $^ -o $@

.PHONY: clean
clean:
		rm -f *.x *.o *~ datos.txt
