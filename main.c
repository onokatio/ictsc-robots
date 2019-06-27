#include <stdio.h>

#define fieldX 60
#define fieldY 20

struct Robot{
	int x;
	int y;
};

struct Player{
	int x;
	int y;
};

int main(void){

	//int robot[fieldX][fieldY];
	struct Robot robot[40];
	struct Player player;

	init(robot);
	init(player);
	
	play();
}

void play(){
	while(true){
		draw();
		input();
		calc();
	}
}
