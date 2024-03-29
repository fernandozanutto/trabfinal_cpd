# MakeFile

all: moviesrating.exe
teste: teste.exe

moviesrating.exe: main.o user.o movie.o trie.o tag.o genre.o clear.o
	g++ -Wall -o moviesrating.exe movie.o user.o trie.o tag.o genre.o clear.o main.o -g -O3 -std=c++17

teste.exe: test.o user.o movie.o trie.o tag.o genre.o clear.o
	g++ -Wall -o teste.exe movie.o user.o trie.o tag.o genre.o clear.o test.o -g -O3 -std=c++17

movie.o:
	g++ -Wall -c src/Movie.cpp -o movie.o -g -O3 -std=c++17

user.o: src/User.cpp src/header/User.h
	g++ -Wall -c src/User.cpp -o user.o -g -O3 -std=c++17

main.o: src/main.cpp src/Hash.cpp src/header/Hash.h
	g++ -Wall -c src/main.cpp -o main.o -g -O3 -std=c++17

trie.o: src/header/Trie.h src/Trie.cpp
	g++ -Wall -c src/Trie.cpp -o trie.o -g -O3 -std=c++17

tag.o: src/header/Tag.h src/Tag.cpp
	g++ -Wall -c src/Tag.cpp -o tag.o -g -O3 -std=c++17

genre.o: src/header/Genre.h src/Genre.cpp
	g++ -Wall -c src/Genre.cpp -o genre.o -O3 -std=c++17
	
clear.o: src/header/ClearString.h src/ClearString.cpp
	g++ -Wall -c src/ClearString.cpp -o clear.o -O3 -std=c++17

test.o: src/test.cpp src/Hash.cpp src/header/Hash.h
	g++ -Wall -c src/test.cpp -o test.o -g -O3 -std=c++17

clean: 
	rm *.o

run: moviesrating.exe clean
	./moviesrating.exe
	
runtest: teste.exe clean
	./teste.exe
