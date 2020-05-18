#include "DigiKeyboard.h"
#include <Adafruit_NeoPixel.h>
int i = 0;
int i2 = 0;
int c = 0;
int rote = 0;
int wheel = 0;

const int ledPin = 1;		   // RGB LED 引脚
const int keyPin = 0;		   // 按键引脚
const int keyPin2 = 2;		   // 按键引脚

int R[13] = {0x00,0xFF,0x00,0xFF,0xFF,0xFF,0xF0,0xD2,0x9F,0xFF,0x00,0x00,0x00};
int G[13] = {0x00,0xFF,0xFF,0x00,0xFF,0x51,0x00,0x00,0x4D,0x00,0xFF,0x00,0x00};
int B[13] = {0x00,0xFF,0xFF,0xFF,0x00,0x51,0x78,0xD2,0x95,0x00,0x00,0xFF,0x00};

int k21[13]={0x1E,0x2b,0x17,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1B,0x06,0x1E,0x1E};
int k22[13]={0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x00,0x00};

int k11[13]={0x27,0x2b,0x1C,0x27,0x27,0x27,0x27,0x27,0x27,0x19,0x19,0x27,0x27};
int k12[13]={0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x00,0x00};

int Brightness = 64; // 亮度值（0-255）

Adafruit_NeoPixel led = Adafruit_NeoPixel(2, ledPin, NEO_GRB + NEO_KHZ800);

uint32_t Wheel(byte WheelPos){
	WheelPos = 255 - WheelPos;
	if (WheelPos < 85){
		return led.Color(255 - WheelPos * 3, 0, WheelPos * 3);
	}
	if (WheelPos < 170){
		WheelPos -= 85;
		return led.Color(0, WheelPos * 3, 255 - WheelPos * 3);
	}
	WheelPos -= 170;
	return led.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void setup(){
	pinMode(keyPin, INPUT_PULLUP);
	pinMode(keyPin2, INPUT_PULLUP);
	led.begin();
	led.setBrightness(Brightness);
	led.show();
}

void loop(){
	
	DigiKeyboard.sendKeyStroke(0);
	if (digitalRead(keyPin) == LOW and digitalRead(keyPin2) != LOW){
		if(i == 0 or i > 10){
			DigiKeyboard.sendKeyStroke(k11[c],k12[c]);
		}
		i++;
	}else{
		i = 0;
	}

	if (digitalRead(keyPin2) == LOW){
		if(i2 == 0 or i2 > 10){
			if(digitalRead(keyPin) == LOW){
				c++;
				if(c > 12){
					c = 0;
				}
				led.setPixelColor(0, R[c], G[c], B[c]);
				led.setPixelColor(1, R[c], G[c], B[c]);
				led.show();
			}else{
				DigiKeyboard.sendKeyStroke(k21[c],k22[c]);
			}
		}
		DigiKeyboard.delay(25);
		i2 ++;
	}else{
		i2 = 0;
	}

	DigiKeyboard.delay(25); // 防抖延时

	if(c == 0){
		led.setPixelColor(0, Wheel((rote) & 255));
		led.setPixelColor(1, Wheel((1+rote) & 255));
		led.show();
		rote++;
		if (rote == 255){
			rote = 0;
		}
	}
	
}

