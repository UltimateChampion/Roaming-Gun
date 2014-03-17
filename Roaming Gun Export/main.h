typedef unsigned short u16;

#define REG_DISPCTL *(u16*) 0x4000000 // Set display control register to location at x4000000

#define MODE3 3// both of these used to enable mode 3
#define BG2_ENABLE (1<<10)

#define SCANLINECOUNTER (*(volatile unsigned short *)0x4000006)
#define RGB(r,g,b) ((r) | (g)<<5 | (b)<<10)


#include "win.h"
#include "titleon.h"
#include "titleoff.h"
#include "lose.h"
#include "portal.h"
#include "howto.h"
#include "rgintro1.h"
#include <stdlib.h>

struct bullet{
int dir;
int x;
int y;
int hit;

};

struct portal {

int x;
int y;

};

struct possibleStarts{

int px;
int py;
int ex;
int ey;

};



//general prototypes
void setPixel(int r, int c, u16 color);
void waitForVblank();
void drawRect(int r, int c, int width, int height, u16 color);
void clearRect(int r, int c, int width, int height);
void drawImage3(int r, int c, int width, int height, const short unsigned *picture);

// player prototypes
int keyMoveCheck();
void handlePlayer();
void playerLogic(int x, int y, int oldx, int oldy, int side);
void drawLife(int x, int y, int life);
void setStartPos();

//bullet prototypes
void handleBullets();
int shootGun();

//enemy prototypes
void drawEnemy(int x, int y, int oldx, int oldy, int invert);
void handlePhantos();
void drawHealth(int x, int y, int health);

// portal prototypes
void handlePortals();


// game modes

void mode0(); //title screen
void mode1();//game
void mode2();//victory screen
void mode3();//lose screen
void mode4();//how to screen

int startPressed();
int selectPressed();
void setVariables();

