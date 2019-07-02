#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern char getChar(void);

#define fieldX 60
#define fieldY 20
#define ROBOTNUM 4

struct Robot_single{
	int x;
	int y;
};

struct Robots{
	struct Robot_single array[ROBOTNUM];
	int RobotField[fieldX][fieldY];
};

struct Player{
	int x;
	int y;
};


void Robots_Setxy(struct Robots *robots, int num, int x, int y){
	robots->array[num].x = x;
	robots->array[num].y = y;
	robots->RobotField[x][y] = 1;
}

void draw(struct Robots *robots,struct Player player){
	int i;
	int j;
	int vram[fieldX][fieldY];
	int vram_old[fieldX][fieldY];


	for(i=0;i<fieldX;i++){
		for(j=0;j<fieldY;j++){
			vram[i][j] = ' ';
		}
	}

	for(i=0;i<ROBOTNUM;i++){
		vram[robots->array[i].x][robots->array[i].y] = '+';
		printf("%d %d \n",robots->array[i].x,robots->array[i].y);
	}

	printf("+");
	for(i=0;i<fieldX;i++){
		printf("-");
	}
	printf("+\n");
	for(j=0;j<fieldY;j++){
		printf("|");
		for(i=0;i<fieldX;i++){
			printf("%c",vram[i][j]);
		}
		printf("|\n");
	}
	printf("+");
	for(i=0;i<fieldX;i++){
		printf("-");
	}
	printf("+\n");
}

int input(){
	char key = getChar();
	if(key == 'a'){
		printf("%c",key);
		return 1;
	}
	return 0;
}

void calc(){
}

void init_robot(struct Robots *robots){
	for(int i=0;i<ROBOTNUM;i++){
		Robots_Setxy(robots, i, rand()%fieldX, rand()%fieldY);
	}
}

void play(){
	int exitflag = 0;
	struct Robots robots = {};
	struct Player player = {};

	init_robot(&robots);

	draw(&robots,player);

	while(!exitflag){
		exitflag = input();
		calc();
	}
}

void init(int array[fieldX][fieldY]){
	int i;
	int j;

	for(i=0;i<fieldX;i++){
		for(j=0;j<fieldY;j++){
			array[i][j] = 0;
		}
	}
	
}

int main(void){

	srand((unsigned)time(NULL));
	play();
}
