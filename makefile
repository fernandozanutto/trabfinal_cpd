# MakeFile

all: moviesrating.exe
test: test.exe

moviesrating.exe: main.o user.o movie.o
	g++ -o moviesrating.exe movie.o user.o main.o -g -std=c++14

test.exe: test.o user.o movie.o
	g++ -o test.exe movie.o user.o main.o -g -std=c++14

movie.o:
	g++ -c src/Movie.cpp -o movie.o -g -std=c++14

user.o: src/User.cpp src/header/User.h
	g++ -c src/User.cpp -o user.o -g -std=c++14

main.o: src/main.cpp src/Hash.cpp src/header/Hash.h src/Trie.cpp src/header/Trie.h
	g++ -c src/main.cpp -o main.o -g -std=c++14


test.o: src/test.cpp src/Hash.cpp src/header/Hash.h src/Trie.cpp src/header/Trie.h
	g++ -c src/test.cpp -o test.o -g -std=c++14

clean: 
	rm *.o

run: moviesrating.exe clean
	./moviesrating.exe
	
runtest: test.exe clean
	./test.exe
