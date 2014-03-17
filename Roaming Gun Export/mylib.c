//AMIER NAJI//
#include "mylib.h"


void setPixel(int x, int y, u16 color) {
    videoBuffer[OFFSET(y, x, WIDTH)] = color;
}


void drawRect(int x, int y, int width, int height, u16 color) {

	
	for (int i = 0; i < height; i++) {
		DMA[3].src = &color;
		DMA[3].dst = &videoBuffer[OFFSET(y+i, x, 240)];
		DMA[3].cnt = (width) | DMA_ON | DMA_SOURCE_FIXED;
	}

}

void clearRect(int x, int y, int width, int height) {
	
	u16 colorpass = 0;
	drawRect(x, y, width, height, colorpass);
}


void drawImage3(int x, int y, int width, int height, const short unsigned *picture) {// draws image using DMA

	for (int i = 0; i < height; i++) {

		DMA[3].src = &picture[i*width];
		DMA[3].dst = &videoBuffer[OFFSET(y+i, x, 240)];
		DMA[3].cnt = (width) | DMA_ON ;

	}

}




