#include <stdio.h>

extern char getChar(void);

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


void draw(){
	int i;
	int j;
	int vram[fieldX][fieldY];

	for(i=0;i<fieldX;i++){
		for(j=0;j<fieldY;j++){
			vram[i][j] = ' ';
		}
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

void play(){
	int exitflag = 0;
	int i;
	int j;
	int vram[fieldX][fieldY];
	int vram_old[fieldX][fieldY];

	for(i=0;i<fieldX;i++){
		for(j=0;j<fieldY;j++){
			vram[i][j] = ' ';
		}
	}

	draw(vram,vram_old);

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

	//int robot[fieldX][fieldY];
	struct Robot robot[40];
	struct Player player;

	play();
}
