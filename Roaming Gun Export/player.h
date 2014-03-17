

#include "rightgun.h"
#include "leftgun.h"
#include "life3.h"
#include "life2.h"
#include "life1.h"
#include "life0.h"

typedef unsigned short u16;
#define BUTTON_A      (1<<0)
#define BUTTON_B      (1<<1)
#define BUTTON_SELECT (1<<2)
#define BUTTON_START  (1<<3)
#define BUTTON_RIGHT  (1<<4)
#define BUTTON_LEFT   (1<<5)
#define BUTTON_UP     (1<<6)
#define BUTTON_DOWN   (1<<7)
#define BUTTON_R      (1<<8)
#define BUTTON_L      (1<<9)



#define PLAYERWIDTH 25
#define PLAYERHEIGHT 25

void clearRect(int r, int c, int width, int height);
void drawRect(int r, int c, int width, int height, u16 color);
void drawImage3(int r, int c, int width, int height, const short unsigned *picture);
int keyMoveCheck();
void playerLogic(int x, int y, int oldx, int oldy, int side);
int shootGun();
void drawLife(int x, int y, int life);
int startPressed();
int selectPressed();


#define BUTTONS (*( volatile unsigned int *)0x04000130)
#define KEY_DOWN_NOW(key)  (~(BUTTONS) & key)
