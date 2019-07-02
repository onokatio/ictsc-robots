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
	int isDead;
};

struct Robots{
	struct Robot_single array[ROBOTNUM];
	int RobotField[fieldX][fieldY];
	int ScrapField[fieldX][fieldY];
	struct Robot_single *RobotField_Pointer[fieldX][fieldY][ROBOTNUM];
};

struct Player{
	int x;
	int y;
};


void Robots_Setxy(struct Robots *robots, int num, int x, int y){
	//struct Robot_single *RobotField_Pointer[fieldX][fieldY][ROBOTNUM];
	robots->array[num].x = x;
	robots->array[num].y = y;
	robots->RobotField[x][y] = 1;
}

void draw(struct Robots *robots,struct Player *player){
	int i;
	int j;
	int vram[fieldX][fieldY];


	for(j=0;j<fieldY;j++){
		for(i=0;i<fieldX;i++){
			vram[i][j] = ' ';
		}
	}

	for(i=0;i<ROBOTNUM;i++){
		if(! robots->array[i].isDead){ vram[robots->array[i].x][robots->array[i].y] = '+'; };
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

void teleport_player(struct Robots *robots, struct Player *player){
	int randx;
	int randy;
	do {
		randx = rand()%fieldX;
		randy = rand()%fieldY;
		player->x=randx;
		player->y=randy;
	} while (robots->RobotField[randx][randy] != 0);
}

void move_player(char key, struct Robots *robots,struct Player *player){
	switch(key){
		case 'h':
			if(! robots->RobotField[player->x -1][player->y]) player->x--;
			break;
		case 'l':
			if(! robots->RobotField[player->x +1][player->y]) player->x++;
			break;
		case 'j':
			if(! robots->RobotField[player->x][player->y +1]) player->y++;
			break;
		case 'k':
			if(! robots->RobotField[player->x][player->y -1]) player->y--;
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
			teleport_player(robots,player);
			break;
	}
	if(player->x > fieldX-1) player->x = fieldX-1;
	if(player->x < 0) player->x = 0;
	if(player->y > fieldY-1) player->y = fieldY-1;
	if(player->y < 0) player->y = 0;
	return;
}

void update_robots(struct Robots *robots,struct Player *player){
	for(int i=0;i<ROBOTNUM;i++){
		if(robots->array[i].x != player->x){

			robots->RobotField[robots->array[i].x][robots->array[i].y]--;

			if(robots->array[i].x < player->x){
				robots->array[i].x++;
			}else{
				robots->array[i].x--;
			}

			robots->RobotField[robots->array[i].x][robots->array[i].y]++;

		}
		if(robots->array[i].y != player->y){

			robots->RobotField[robots->array[i].x][robots->array[i].y]--;

			if(robots->array[i].y < player->y){
				robots->array[i].y++;
			}else{
				robots->array[i].y--;
			}

			robots->RobotField[robots->array[i].x][robots->array[i].y]++;

		}
		if(robots->array[i].x == player->x && robots->array[i].y == player->y){
			draw(robots,player);
			printf("Game Over");
			exit(0);
		}
	}
	for(int y=0; y < fieldY ; y++){
		for(int x=0; x < fieldX ; x++){
			if(robots->RobotField[x][y] >= 2){
			}
		}
	}

}

int calc(char key,struct Robots *robots,struct Player *player){
	switch(key){
		case 'h':
		case 'l':
		case 'j':
		case 'k':
		case 'u':
		case 'i':
		case 'n':
		case 'm':
		case '0':
			move_player(key,robots,player);
			update_robots(robots,player);
			break;
		case '5':
			update_robots(robots,player);
			break;
		default:
			break;

	}
	return 0;
}

void init_robots(struct Robots *robots){
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
	char key;

	init_robots(&robots);
	init_player(&player);

	draw(&robots,&player);

	while(!exitflag){
		key = getChar();
		//printf("%c\n",key);
		calc(key,&robots,&player);
		draw(&robots,&player);
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
