//AMIER NAJI//
#include "player.h"


int shotdown = 0; //check if the shoot button is down
int startdown = 0;
int selectdown = 0;


// send out an integer checking what movement keys are down at a time (allows for diagonal movement)
int keyMoveCheck() {

	int out = 0;
	
	if (KEY_DOWN_NOW(BUTTON_LEFT)) {

		out = out | 1<<0;

	}

	if (KEY_DOWN_NOW(BUTTON_RIGHT)) {

		out = out | 1<<1;

	}

	if (KEY_DOWN_NOW(BUTTON_UP)) {

		out = out | 1<<2;

	}

	if (KEY_DOWN_NOW(BUTTON_DOWN)) {

		out = out | 1<<3;

	}

	return out;

}

//return whether or not the player shot the gun
int shootGun() {


	if (shotdown == 1 && !(KEY_DOWN_NOW(BUTTON_A))) {
		
		shotdown = 0;
		return 1;
	
	}

	if (KEY_DOWN_NOW(BUTTON_A)) {
		shotdown = 1;
	}

	return 0;



}


// is start pressed?
int startPressed() {


	if (startdown == 1 && !(KEY_DOWN_NOW(BUTTON_START))) {
		
		startdown = 0;
		return 1;
	
	}

	if (KEY_DOWN_NOW(BUTTON_START)) {
		startdown = 1;
	}

	return 0;



}


// is select pressed?
int selectPressed() {


	if (selectdown == 1 && !(KEY_DOWN_NOW(BUTTON_SELECT))) {
		
		selectdown = 0;
		return 1;
	
	}

	if (KEY_DOWN_NOW(BUTTON_SELECT)) {
		selectdown = 1;
	}

	return 0;

}



//clear out the original position and draw a new drawing of the gun depending on the direction you are facing
void playerLogic(int x, int y, int oldx, int oldy, int side) {


	drawRect(oldx, oldy, PLAYERWIDTH, PLAYERHEIGHT, 0);

	(side == 1) ? drawImage3(x, y, PLAYERWIDTH, PLAYERHEIGHT, rightgun) : drawImage3(x, y, PLAYERWIDTH, PLAYERHEIGHT, leftgun) ;

}


//draw out how many lives you have
void drawLife(int x, int y, int life) {



	drawRect(x, y, LIFE3_WIDTH, LIFE3_HEIGHT, 0);

	switch(life) {

	case 0: drawImage3(x, y, LIFE3_WIDTH, LIFE3_HEIGHT, life0);
		break;
	case 1: drawImage3(x, y, LIFE3_WIDTH, LIFE3_HEIGHT, life1);
		break;
	case 2: drawImage3(x, y, LIFE3_WIDTH, LIFE3_HEIGHT, life2);
		break;
	case 3: drawImage3(x, y, LIFE3_WIDTH, LIFE3_HEIGHT, life3);
		break;
		
	}


}
