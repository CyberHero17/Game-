default_build: main.cpp	Entity.hpp Entity.cpp Player.hpp Player.cpp Structures.cpp Zombie.cpp Zombie.hpp
	g++ main.cpp Entity.cpp Player.cpp Zombie.cpp -o main -lsfml-graphics -lsfml-window -lsfml-system
	./main

clean:
	rm main
