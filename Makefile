all:
	g++ src/voronoi.cpp src/app.cpp -w -lSDL2 -lSDL2_image -o bin/app
