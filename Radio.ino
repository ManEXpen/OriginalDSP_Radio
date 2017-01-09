
//Radio.ino

#include <Wire.h>


void i2c_send(int addr, int value);
int i2c_read(int addr);

const int dev_addr = 0x10; //M6951のデバイスIDらしい・・・

void setup() {
  Wire.bigin();

}

void loop() {
  // put your main code here, to run repeatedly:
}

void i2c_send(int addr, int value){
	Wire.biginTransmission(dev_addr);
	Wire.write(addr);
	Wire.write(value);
	Wire.endTransmission();
	delay(3);
}

int i2c_read(int addr){
	Wire.biginTransmission(dev_addr);
	Wire.write(addr);
	Wire.endTransmission();
	Wire.requestFrom(dev_addr, 8);
	return Wire.read();
}