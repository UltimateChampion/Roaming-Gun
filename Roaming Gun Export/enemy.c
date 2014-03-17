//AMIER NAJI//
#include "enemy.h"



void drawEnemy(int x, int y, int oldx, int oldy, int invert) {// draws phantos

drawRect(oldx, oldy, PHANTOS_WIDTH, PHANTOS_HEIGHT, 0);
//clearRect(oldy, oldx, PHANTOS_WIDTH, PHANTOS_HEIGHT);
(invert == 0) ? drawImage3(x, y, PHANTOS_WIDTH, PHANTOS_HEIGHT, phantos) : drawImage3(x, y, PHANTOS2_WIDTH, PHANTOS2_HEIGHT, phantos2);


}


void drawHealth(int x, int y, int health) {// depending on the input, will change the enemy health bar to current health


drawRect(x, y, ENHEALTH5_WIDTH, ENHEALTH5_HEIGHT, 0);

switch( health ) {


case 5: drawImage3(x, y, ENHEALTH5_WIDTH, ENHEALTH5_HEIGHT, enhealth5);
	break;
case 4: drawImage3(x, y, ENHEALTH4_WIDTH, ENHEALTH4_HEIGHT, enhealth4);
	break;
case 3: drawImage3(x, y, ENHEALTH3_WIDTH, ENHEALTH3_HEIGHT, enhealth3);
	break;
case 2: drawImage3(x, y, ENHEALTH2_WIDTH, ENHEALTH2_HEIGHT, enhealth2);
	break;
case 1: drawImage3(x, y, ENHEALTH1_WIDTH, ENHEALTH1_HEIGHT, enhealth1);
	break;
case 0: drawImage3(x, y, ENHEALTH0_WIDTH, ENHEALTH0_HEIGHT, enhealth0);
	break;
default: drawImage3(x, y, ENHEALTH0_WIDTH, ENHEALTH0_HEIGHT, enhealth0);
	break;




}

}
