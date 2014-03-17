//AMIER NAJI//
#include "main.h"

//clock and game variables
int clock = 0;
int mode = 0;

//player variables
int playerx = 50;
int playery = 60;
int side = 1;
int walkspeed = 3;
int canShoot = 1;
int updateCanShoot = 0;
int life = 3;

struct bullet *ammo;

//


//enemy variables
int xen = 80;
int yen = 80;
int xenmove = 3;
int yenmove = 3;
int enemIsHit = 0;
int enemHealth = 15;
int nextHitChange= 0;
//

//portal variables

int portal1x = 10;		
int portal1y = 50;	

int portal2x = 105;
int portal2y = 10;

int portal3x = 210;
int portal3y = 80;
//




int main(void){ 

	
	

	REG_DISPCTL = MODE3 | BG2_ENABLE; // set display register to mode 3
	ammo = malloc(40);// allocate space for ammo;


	int preStart = 0;
	int i = 0;

	drawImage3(0, 0, TITLEON_WIDTH, TITLEON_HEIGHT, rgintro1);
	while (preStart < 10000) {

		if (i > 100) {
		preStart++;
		i= 0;
		}

		i++;
	}


	while(1) {

	clock++;

	if (selectPressed()) { // if select is pressed, reset
	mode = 0;
	}

	if (clock == 100000000) {
	clock = 0;	
	
	}
		switch(mode) {// decide what game mode to go with
	
		case 0: mode0();
			break;
		case 1: mode1();
			break;
		case 2: mode2();
			break;
		case 3: mode3();
			break;	
		case 4: mode4();
			break;	

		}		
		
	}
}

//start screen
void mode0(){

	if ((clock % 32000) == 0) {
	drawImage3(0, 0, TITLEON_WIDTH, TITLEON_HEIGHT, titleon);
	}

	if ((clock % 64000) == 0) {
	drawImage3(0, 0, TITLEOFF_WIDTH, TITLEOFF_HEIGHT, titleoff);
	}

	if (startPressed()) {

	mode = 4;
	}

}

//how to play screen
void mode4() {

drawImage3(0, 0, HOWTO_WIDTH, HOWTO_HEIGHT, howto);

	if (startPressed()) {
	free(ammo);
	setVariables();
	drawRect(0,0, 240, 160, 0);	
	drawHealth(20, 135, (enemHealth/3));
	drawLife(180, 135 , life);
	setStartPos();

	mode = 1;
	}

}

//win screen
void mode2(){

	drawImage3(0, 0, 240, 160, win);
	
	if ((clock % 500) == 0) {
	drawRect(0, 0, 240, 160, 0);
	enemHealth = 5;
	life = 3;
	mode = 0;
	}

}

//lose screen
void mode3(){

	drawImage3(0, 0, 240, 160, lose);

	if ((clock % 500) == 0) {
	drawRect(0, 0, 240, 160, 0);
	enemHealth = 5;
	life = 3;
	mode = 0;
	}
}

//game
void mode1() {

	if ((clock % 20000) == 0) { // limit how many bullets we can shoot in a specific period
		canShoot = 1;
	}

	if ((clock%1000)== 0) {
	
		waitForVblank();// calls vblank to do computational stuff before the video gets written to screen
		
		handlePlayer();
		handlePhantos();
		handlePortals();
		handleBullets();
		
		if (enemHealth == 0) {// if enemy is dead, you win
		
		mode = 2;
		clock = 1;
		}

		if (life == 0) {// if you die, you lose
		
		mode = 3;
		clock = 1;
		}

	}



}



void waitForVblank() {
	while(SCANLINECOUNTER > 160);
	while(SCANLINECOUNTER < 160);
}





void handlePlayer() {

	//collision check with enemy
	if ((abs(playery-(yen+7)) < 15) && (abs(playerx-xen+7) < 20)) {

		setStartPos();

		life--;
		drawLife(180, 135 , life);
	
		if (life == 0) {

		mode = 3;

		}
	
	}


	// checks what keys are pressed down to take care of player
	int result = keyMoveCheck();


	if ((result & (1<<0))) {
			side = -1;

			if ((playerx-2) > 0) {
				playerLogic(playerx-2, playery, playerx, playery, side);
				playerx -= walkspeed;
			}

		}

		if ((result & (1<<1))) {
			side = 1;

			if ((playerx+2) < 220) {
				playerLogic(playerx+2, playery, playerx, playery, side);
				playerx += walkspeed;

			}
		}

		if ((result & (1<<2))) {

			if ((playery-2) > 0) {
				playerLogic(playerx, playery-2, playerx, playery, side);
				playery -= walkspeed;
			}
		}

		if ((result & (1<<3))) {

			if ((playery+2) < 110) {
				playerLogic(playerx, playery+2, playerx, playery, side);
				playery += walkspeed;
			}
		}

}


void handleBullets() {

	
	struct bullet *temp = ammo;
	int i = 0;

	// if the user shoots the gun, make a bullet structure for it
	if (shootGun() && canShoot) {
		
		canShoot = 0;
		updateCanShoot = clock + 50;

		while(i < 10) {

			if ((temp -> dir) == 0) {
		
			temp -> dir = side;
			temp -> x = playerx + 14;
			temp -> y = playery + 10;
			temp -> hit = 0;

			break;
	
			}
			temp++; 
			i++;

		} 
	}

	
	temp = ammo;
	// loop through all of the bullet structures updating their current positions
	i = 0;
	while(i < 10) {

		if ((temp -> dir) != 0) {


			int currx = temp -> x;
			int curry = temp ->y;
			int currdir = temp -> dir;



			if ((abs(curry-(yen+7)) < 7) && (abs(currx-xen+7) < 20)) {
	

				if ((temp -> hit) == 0)	{
			
					temp -> hit = 1;
					enemHealth -= 1;

				}

				enemIsHit = 1;
			
	
			}

			setPixel(currx, curry, 0);

			if  ( ((currx + currdir*5) > 220)||((currx + currdir*5) < 15) ) {

			temp -> dir = 0;
		
			}

			else {
			temp -> x = (temp -> x) + (temp -> dir) * 5;

			setPixel(temp -> x, temp ->y, RGB(31,31,31));

			}


		}
		temp++; 
		i++;

	} 


}

void handlePhantos() {

	//occasionally randomizes the direction that phantos moves
	if ((clock % 100000) == 0) {

		xenmove = ((rand()%10) > 5) ? (rand()%3) +1: ((rand()%4)*(-1)) -1 ; 
		yenmove = ((rand()%10) > 5) ? (rand()%2) +1: ((rand()%3)*(-1)) -1 ; 

	}

	// change the enemy sprite back to normal occasionally
	if ((clock % 2000) == 0) {
		enemIsHit = 0;

	}

	int oldxen = xen;
	int oldyen = yen;

	//boundary checking
	if (((xen + xenmove) >210) || ((xen + xenmove) <10)) {
	
		xenmove = -xenmove;

	}

	if (((yen + yenmove) >120) || ((yen + yenmove) <10)) {
	
		yenmove = -yenmove;

	}

	xen = xen + xenmove;
	yen = yen + yenmove;
	// change the sprite accordingly, if the enemy is hit or not

	(enemIsHit==0) ? drawEnemy(xen,yen, oldxen, oldyen, 0): drawEnemy(xen,yen, oldxen, oldyen, 1);


	//draw enemy health
	if ((enemHealth%3) == 0) {
	
	drawHealth(20, 135, (enemHealth/3));

	}

}


void handlePortals() {

	//draw all the portals
	drawImage3(portal1x, portal1y, PORTAL_WIDTH, PORTAL_HEIGHT, portal);
	drawImage3(portal2x, portal2y, PORTAL_WIDTH, PORTAL_HEIGHT, portal);
	drawImage3(portal3x, portal3y, PORTAL_WIDTH, PORTAL_HEIGHT, portal);

	//if player touches portal 1, they can be moved to either portal 2 or 3
	if ((abs(playery-(portal1y)) < 12) && (abs(playerx-portal1x) < 10)) {

		if ((rand() % 2) == 0) {

		playerLogic(portal2x-5, portal2y+20, playerx, playery, side);
		playerx = portal2x-5;
		playery = portal2y+20;	
		}
			else {
			playerLogic(portal3x-25, portal3y, playerx, playery, side);
			playerx = portal3x-25;
			playery = portal3y;	
			}
	}
	
	else if ((abs(playery-(portal2y)) < 15) && (abs(playerx-portal2x) < 15)) { //if player touches portal 2, they can be moved to either portal 1 or 3

			if ((rand() % 2) == 0) {

			playerLogic(portal1x+20, portal1y, playerx, playery, side);
			playerx = portal1x+20;
			playery = portal1y;	

			}

			else {
			playerLogic(portal3x-25, portal3y, playerx, playery, side);
			playerx = portal3x-25;
			playery = portal3y;	
			}

	}


	else if ((abs(playery-(portal3y)) < 15) && (abs(playerx-portal3x) < 15)) { //if player touches portal 3, they can be moved to either portal 2 or 1

			if ((rand() % 2) == 0) {

			playerLogic(portal1x+20, portal1y, playerx, playery, side);
			playerx = portal1x+20;
			playery = portal1y;	

			}
				else {

				playerLogic(portal2x-5, portal2y+20, playerx, playery, side);
				playerx = portal2x-5;
				playery = portal2y+20;		

				}

	}

}


//set the starting positions for the player and phantos randomly
void setStartPos() {

int randomint = rand();


	int opx = playerx;
	int opy = playery;
	int oenx = xen;
	int oeny = yen;
	switch(randomint%3) {

		case 0:
		playerx = 50;
		playery = 60;
		xen = 150;
		yen = 100;
		break;

		case 1:

		xen = 50;
		yen = 60;
		playerx = 150;
		playery = 100;
		break;

		case 2:

		playerx = 100;
		playery = 90;
		xen = 20;
		yen = 40;
		break;

	}

	drawEnemy(xen,yen, oenx, oeny, 0);
	playerLogic(playerx, playery, opx, opy, side);

}

void setVariables() {// for reset and initializing the game

	//player variables
	playerx = 50;
	playery = 60;
	side = 1;
	walkspeed = 3;
	canShoot = 1;
	updateCanShoot = 0;
	life = 3;

	ammo=malloc(40);// allocate space for bullet information

	//


	//enemy variables
	xen = 80;
	yen = 80;
	xenmove = 3;
	yenmove = 3;
	enemIsHit = 0;
	enemHealth = 15;
	nextHitChange= 0;
	//

	//portal variables

	portal1x = 10;		
	portal1y = 50;	

	portal2x = 105;
	portal2y = 10;

	portal3x = 210;
	portal3y = 80;
	
	ammo=malloc(40);// allocate space for bullet information

}
