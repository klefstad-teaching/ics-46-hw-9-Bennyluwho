CXXFLAGS=-ggdb -std=c++20 -Wextra -Wfatal-errors -pedantic
dijkstras_main: src/dijkstras.cpp   src/dijkstras_main.cpp
	g++ $(CXXFLAGS) -o dijkstras_main  src/dijkstras.cpp	src/dijkstras_main.cpp
ladder_main: src/ladder.cpp   src/ladder_main.cpp
	g++ $(CXXFLAGS) -o ladder_main  src/ladder.cpp   src/ladder_main.cpp
clean:
	/bin/rm ladder_main dijkstras_main

memcheck: ladder_main
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./main