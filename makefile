# MakeFile

all: moviesrating.exe

moviesrating.exe: main.o user.o movie.o
	g++ -o moviesrating.exe movie.o user.o main.o -g

movie.o:
	g++ -c src/Movie.cpp -o movie.o -g

#trie.o: 
#	g++ -c src/Trie.cpp -o trie.o

user.o: src/User.cpp src/header/User.h
	g++ -c src/User.cpp -o user.o -g

main.o: src/main.cpp src/Hash.cpp src/header/Hash.h
	g++ -c src/main.cpp -o main.o -g


clean: 
	rm *.o

run: moviesrating.exe clean
	./moviesrating.exe
