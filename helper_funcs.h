#ifndef HELPER_FUNCS
#define HELPER_FUNCS

#include "init_funcs.h"

uint32_t generate_random_position(uint32_t min, uint32_t max) {

    uint32_t range = max - min + 1;
    uint32_t value = 0;

    HAL_RNG_GenerateRandomNumber(&hrng, &value);

    return (value % range) + min;
}

int getAverageGyroReading() {

	uint16_t numberOfReadings = 10;
	int sum = 0;
	float xyz[3];

	for(uint8_t i = 0; i < numberOfReadings; ++i) {
		BSP_GYRO_GetXYZ(xyz);
		sum += (int) xyz[1];
	}
	return (sum / numberOfReadings);
}

void drawHeart(uint16_t x, uint16_t y,uint32_t color){
	uint8_t length=11;
	for(int i=0; i<11;i++){
		if(i==0){
			drawHLine(x+2,y,3,color);
			drawHLine(x+8,y,3,color);
		}else if(i==1){
			drawHLine(x+1,y+i,5,color);
			drawHLine(x+7,y+i,5,color);
		}else if(i<=4){
			drawHLine(x,y+i,13,color);
		}else{ drawHLine(x+i-4,y+i,length,color);
			length-=2;
		}
	}
}

void drawHLine(uint16_t xCoord, uint16_t yCoord, uint16_t length, uint32_t color){
	uint32_t *ptr = (uint32_t*) (FRAME_BUF_1_ADDRESS);
	ptr+=(yCoord*LCD_WIDTH)+xCoord;
	for(int i = 0; i<length;i++)
		*(ptr + i) = color;
}

#endif
