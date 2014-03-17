#ifndef ENEMY_H
#define ENEMY_H

typedef unsigned short u16;
#include "phantos.h"
#include "phantos2.h"

#include "enhealth5.h"
#include "enhealth4.h"
#include "enhealth3.h"
#include "enhealth2.h"
#include "enhealth1.h"
#include "enhealth0.h"


void drawEnemy(int x, int y, int oldx, int oldy, int invert);
void drawImage3(int r, int c, int width, int height, const short unsigned *picture);
void clearRect(int r, int c, int width, int height);
void drawRect(int r, int c, int width, int height, u16 color);
void drawHealth(int x, int y, int health);

#endif
