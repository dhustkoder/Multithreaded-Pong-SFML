CC=g++ -std=c++14 pong.cpp -lsfml-system -lsfml-window -lsfml-graphics
OUT= -opong.out

all:
	$(CC) $(OUT)
