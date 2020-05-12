#include "DigiKeyboard.h"
#include <Adafruit_NeoPixel.h>
int i = 0;
int i2 = 0;
int c = 0;
const int ledPin = 1;		   // RGB LED 引脚
const int keyPin = 0;		   // 按键引脚
const int keyPin2 = 2;		   // 按键引脚
int R[] = {0xFF,0x00,0xFF,0xFF,0xFF,0xF0,0xD2,0x6F,0x28,0x00,0x8C,0xF9,0xFF,0xAD,0x5C,0x73,0x9F,0xFF,0x00,0x00};
int G[] = {0xFF,0xFF,0x00,0xFF,0x51,0x00,0x00,0x00,0x28,0xCA,0xEA,0xF9,0x80,0x5A,0xAD,0x73,0x4D,0x00,0xFF,0x00};
int B[] = {0xFF,0xFF,0xFF,0x00,0x51,0x78,0xD2,0xD2,0xFF,0xCA,0x00,0x00,0x00,0x5A,0xAD,0xB9,0x95,0x00,0x00,0xFF};
int Brightness = 100; // 亮度值（0-255）

Adafruit_NeoPixel led = Adafruit_NeoPixel(1, ledPin, NEO_GRB + NEO_KHZ800);

void setup(){
	pinMode(keyPin, INPUT_PULLUP);
	pinMode(keyPin2, INPUT_PULLUP);
	led.begin();
	led.show();
	led.setBrightness(Brightness);
	led.setPixelColor(0, R[0], G[0], B[0]);
	led.show();
}

void loop(){
	DigiKeyboard.sendKeyStroke(0);
	if (digitalRead(keyPin) == LOW){
		if(i == 0 or i > 10){
			DigiKeyboard.sendKeyStroke(KEY_Y);
		}
		i++;
	}else{
		i = 0;
	}

	if (digitalRead(keyPin2) == LOW){
		if(i2 == 0 or i2 > 10){
			led.setPixelColor(0, R[c], G[c], B[c]);
			led.show();
			delay(50);
			c++;
			if(c > sizeof(R)){
				c = 0;
			}
		}
		i2 ++;
	}else{
		i2 = 0;
	}
	DigiKeyboard.delay(50); // 防抖延时
}