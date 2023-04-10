#include "../Inc/target.h"
#include <stdbool.h>


static void drawFilledSquareLCD(uint16_t LCD_WIDTH,uint16_t LCD_HEIGHT,uint8_t FRAME_BUF_1, uint8_t FRAME_BUF_2,
		uint32_t FRAME_BUF_1_ADDRESS, uint32_t FRAME_BUF_2_ADDRESS, uint8_t frameBufIndex, uint32_t color, struct Target *this)
{
//    color = (COLOR_MASK - color) | ALPHA_MASK;

    uint32_t *ptr;
    uint8_t size=this->size;
    if (frameBufIndex == FRAME_BUF_1)
    {
        ptr = (uint32_t *)(FRAME_BUF_1_ADDRESS);
    }
    else if (frameBufIndex == FRAME_BUF_2)
    {
        ptr = (uint32_t *)FRAME_BUF_2_ADDRESS;
    }
    else
    {
        return;
    }

    if (size & 1)
    {
        return;
    }
    size >>= 1;
    uint16_t startX = this->base.xCoord - size, startY = this->base.yCoord - size,
             endX = this->base.xCoord + size, endY = this->base.yCoord + size;
    if (startX > LCD_WIDTH || startY > LCD_HEIGHT || endX > LCD_WIDTH || endY > LCD_HEIGHT)
    {
        return;
    }

    uint16_t i, j;
    for (i = startY; i <= endY; ++i)
    {
        for (j = startX; j <= endX; ++j)
        {
            if (i == 0)
            {
                *(ptr + j) = color;
            }
            else
            {
                *(ptr + (i - 1) * LCD_WIDTH + j) = color;
            }
        }
    }
}

static bool isWithingRange(struct Target *targetA, struct Target *targetB){
	if( sqrt(((targetA->base.xCoord-targetB->base.xCoord)
		    *(targetA->base.xCoord-targetB->base.xCoord))
		    +((targetA->base.yCoord-targetB->base.yCoord)
		    *(targetA->base.yCoord-targetB->base.yCoord)))
		    < (sqrt(2) * targetA->size)){
		    	return true;
	}else return false;
}



cTarget* newTarget(uint16_t coordX, uint16_t coordY, uint8_t s, bool isActive) {
	cTarget* newTarget = malloc(sizeof(cTarget));
	newTarget->base.xCoord = coordX;
	newTarget->base.yCoord= coordY;
	newTarget->size = s;
	newTarget->isActive = isActive;
	newTarget->drawFilledSquareLCD=&drawFilledSquareLCD;
	newTarget->isWithingRange=&isWithingRange;
	return newTarget;
}
