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

void draw(struct Robots *robots,struct Player *player){
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
	}

	vram[player->x][player->y] = '@';

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

void move_player(char key, struct Player *player, struct Robots *robots){
	switch(key){
		case 'h':
			robots->RobotField[player->x -1][player->y] || player->x--;
			break;
		case 'l':
			robots->RobotField[player->x +1][player->y] || player->x++;
			break;
		case 'j':
			robots->RobotField[player->x][player->y +1] || player->y++;
			break;
		case 'k':
			robots->RobotField[player->x][player->y -1] || player->y--;
			break;
		case 'u':
			if(! robots->RobotField[player->x -1][player->y -1]){
				player->x--;
				player->y--;
			}
			break;
		case 'i':
			if(! robots->RobotField[player->x +1][player->y -1]){
				player->x++;
				player->y--;
			}
			break;
		case 'n':
			if(! robots->RobotField[player->x -1][player->y +1]){
				player->x--;
				player->y++;
			}
			break;
		case 'm':
			if(! robots->RobotField[player->x +1][player->y +1]){
				player->x++;
				player->y++;
			}
			break;
		case '0':
			int randx = rand()%fieldX;
			int randy = rand()%fieldY;
			if(! robots->RobotField[randx][randy]){
				player->x++;
				player->y++;
			}
			break;
	}
}

int calc(char key,struct Player *player, struct Robots *robots){
	switch(key){
		case 'h':
		case 'l':
		case 'j':
		case 'k':
		case 'u':
		case 'i':
		case 'n':
		case 'm':
			move_player();
			update_robots();
			break;
		case '0':
			teleport();
			update_robots();
			break;

	}
	return 0;
}

void init_robot(struct Robots *robots){
	for(int i=0;i<ROBOTNUM;i++){
		Robots_Setxy(robots, i, rand()%fieldX, rand()%fieldY);
	}
}

void init_player(struct Player *player){
	player->x = rand()%fieldX;
	player->y = rand()%fieldY;
}

void play(){
	int exitflag = 0;
	struct Robots robots = {};
	struct Player player = {};
	int request_reload = 0;
	char key;

	init_robot(&robots);
	init_player(&player);

	draw(&robots,&player);

	while(!exitflag){
		key = getChar();
		calc(key);
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
