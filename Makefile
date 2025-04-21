default_build_Max: main.cpp	Entity.hpp Entity.cpp Player.hpp Player.cpp Structures.cpp Structures.hpp Zombie.cpp Zombie.hpp Tear.hpp Tear.cpp Item.cpp Item.hpp Breakfast.cpp Breakfast.hpp 
	g++ main.cpp Entity.cpp Player.cpp Zombie.cpp Structures.cpp Tear.cpp Item.cpp Breakfast.cpp -o main -lsfml-graphics -lsfml-window -lsfml-system -L tinyxml2_x64-linux/lib/ -ltinyxml2
default_build_Kirill: main.cpp	Entity.hpp Entity.cpp Player.hpp Player.cpp Structures.cpp Zombie.cpp Zombie.hpp
	g++ main.cpp Entity.cpp Player.cpp Zombie.cpp -o main -lsfml-graphics -lsfml-window -lsfml-system 
	./main

clean:
	rm main
add:
	git status
	git add *.cpp *.hpp Makefile
	git status
