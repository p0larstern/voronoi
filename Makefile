all:
	g++ src/voronoi.cc src/app.cpp -w -lSDL2 -lSDL2_image -o bin/app
