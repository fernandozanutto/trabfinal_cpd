# MakeFile

all: moviesrating.exe
teste: teste.exe

moviesrating.exe: main.o user.o movie.o trie.o tag.o
	g++ -Wall -o moviesrating.exe movie.o user.o trie.o tag.o main.o -g -std=c++14

teste.exe: test.o user.o movie.o trie.o tag.o
	g++ -Wall -o teste.exe movie.o user.o trie.o tag.o test.o -g -O3 -std=c++14

movie.o:
	g++ -Wall -c src/Movie.cpp -o movie.o -g -O3 -std=c++14

user.o: src/User.cpp src/header/User.h
	g++ -Wall -c src/User.cpp -o user.o -g -O3 -std=c++14

main.o: src/main.cpp src/Hash.cpp src/header/Hash.h
	g++ -Wall -c src/main.cpp -o main.o -g -O3 -std=c++14

trie.o: src/header/Trie.h src/Trie.cpp
	g++ -Wall -c src/Trie.cpp -o trie.o -g -O3 -std=c++14

tag.o: src/header/Tag.h src/Tag.cpp
	g++ -Wall -c src/Tag.cpp -o tag.o -g -O3 -std=c++14

test.o: src/test.cpp src/Hash.cpp src/header/Hash.h
	g++ -Wall -c src/test.cpp -o test.o -g -O3 -std=c++14

clean: 
	rm *.o

run: moviesrating.exe clean
	./moviesrating.exe
	
runtest: teste.exe clean
	./teste.exe
