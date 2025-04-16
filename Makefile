default_build: main.cpp	Entity.hpp Entity.cpp Player.hpp Player.cpp Structures.cpp Structures.hpp Zombie.cpp Zombie.hpp Tear.hpp Tear.cpp
	g++ main.cpp Entity.cpp Player.cpp Zombie.cpp Structures.cpp Tear.cpp -o main -lsfml-graphics -lsfml-window -lsfml-system
	./main

clean:
	rm main
add:
	git status
	git add *.cpp *.hpp Makefile
	git status