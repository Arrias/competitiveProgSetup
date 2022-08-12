all: A

bin/A.o: src/A.cpp
	g++ -std=c++2a -D_debug src/A.cpp -o bin/A.o

A: bin/A.o
	./bin/A.o < input.txt
	
bin/B.o: src/B.cpp
	g++ -std=c++2a -D_debug src/B.cpp -o bin/B.o
B: bin/B.o
	./bin/B.o < input.txt

bin/C.o: src/C.cpp
	g++ -std=c++2a -D_debug src/C.cpp -o bin/C.o
C: bin/C.o
	./bin/C.o < input.txt

bin/D.o: src/D.cpp
	g++ -std=c++2a -D_debug src/D.cpp -o bin/D.o
D: bin/D.o
	./bin/D.o < input.txt

bin/E.o: src/E.cpp
	g++ -std=c++2a -D_debug src/E.cpp -o bin/E.o
E: bin/E.o
	./bin/E.o < input.txt

bin/F.o: src/F.cpp
	g++ -std=c++2a -D_debug src/F.cpp -o bin/F.o
F: bin/F.o
	./bin/F.o < input.txt
# < input.txt

bin/G.o: src/G.cpp
	g++ -std=c++2a -D_debug src/G.cpp -o bin/G.o
G: bin/G.o
	./bin/G.o < input.txt

bin/H.o: src/H.cpp
	g++ -std=c++2a -D_debug src/H.cpp -o bin/H.o
H: bin/H.o
	./bin/H.o < input.txt

bin/I.o: src/I.cpp
	g++ -std=c++2a -D_debug src/I.cpp -o bin/I.o
I: bin/I.o
	./bin/I.o < input.txt

bin/J.o: src/J.cpp
	g++ -std=c++2a -D_debug src/J.cpp -o bin/J.o
J: bin/J.o
	./bin/J.o < input.txt

bin/K.o: src/K.cpp
	g++ -std=c++2a -D_debug src/K.cpp -o bin/K.o
K: bin/K.o
	./bin/K.o < input.txt

bin/L.o: src/L.cpp
	g++ -std=c++2a -D_debug src/L.cpp -o bin/L.o
L: bin/L.o
	./bin/L.o < input.txt

bin/M.o: src/M.cpp
	g++ -std=c++2a -D_debug src/M.cpp -o bin/M.o
M: bin/M.o
	./bin/M.o < input.txt

bin/N.o: src/N.cpp
	g++ -std=c++2a -D_debug src/N.cpp -o bin/N.o
N: bin/N.o
	./bin/N.o < input.txt

bin/stupid.o: src/stupid.cpp
	g++ -std=c++2a -D_debug src/stupid.cpp -o bin/stupid.o
stupid: bin/stupid.o
	./bin/stupid.o < input.txt

bin/gen.o: src/gen.cpp 
	g++ -std=c++2a -D_debug src/gen.cpp -o bin/gen.o -I src/lib/gen/gen_fucnctions.h
gen: bin/gen.o
	./bin/gen.o < input.txt

bin/checker.o: src/checker.cpp
	g++ -std=c++2a -D_debug src/checker.cpp -o bin/checker.o  
checker: bin/checker.o
	./bin/checker.o < input.txt

stress:	src/stress
	./src/stress A

	

