# MakeFile

all: moviesrating.exe
teste: teste.exe

moviesrating.exe: main.o user.o movie.o trie.o clear.o
	g++ -o moviesrating.exe movie.o user.o trie.o clear.o main.o -g -std=c++14

teste.exe: test.o user.o movie.o trie.o clear.o
	g++ -o teste.exe movie.o user.o trie.o clear.o test.o -g -O3 -std=c++14

movie.o:
	g++ -c src/Movie.cpp -o movie.o -g -O3 -std=c++14

user.o: src/User.cpp src/header/User.h
	g++ -c src/User.cpp -o user.o -g -O3 -std=c++14

main.o: src/main.cpp src/Hash.cpp src/header/Hash.h
	g++ -c src/main.cpp -o main.o -g -O3 -std=c++14

trie.o: src/header/Trie.h src/Trie.cpp
	g++ -c src/Trie.cpp -o trie.o -g  -O3 -std=c++14

clear.o: src/ClearString.cpp src/header/ClearString.h
	g++ -c src/ClearString.cpp -o clear.o -O3 -std=c++14

test.o: src/test.cpp src/Hash.cpp src/header/Hash.h
	g++ -c src/test.cpp -o test.o -g -O3 -std=c++14

clean: 
	rm *.o

run: moviesrating.exe clean
	./moviesrating.exe
	
runtest: teste.exe clean
	./teste.exe
