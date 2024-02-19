all:
	g++ -I src/include -L src/lib -o main main.cpp init.cpp media.cpp Ball.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image