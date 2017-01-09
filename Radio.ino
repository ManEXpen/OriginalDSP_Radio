
//データシートを参考にしよう！
//http://aitendo3.sakura.ne.jp/aitendo_data/product_img/radio/dsp/m_pcb/m6951/M6951_dshver20130625.pdf

#include <Wire.h>

#define DEFAULT_SETTING 0b10100000 //on, am, no-seek, no-seekup, no-mute, rsv, rsv

void i2c_send(int addr, int value);
int i2c_read(int addr);

const int dev_addr = 0x10; //M6951のデバイスIDらしい・・・

void setup() {
  Wire.begin();
  i2c_send(0x00, DEFAULT_SETTING);
  i2c_send(0x01, 0b00001000);//AM(520-1710KHz, 5KHz Step)
  i2c_send(0x09, 0b00001111);//volume can control by I2C 

  i2c_send(0x06, 0b10110101);//Volume(45)

  delay(10);

 // int AMkhz = 1440;
  int channel = (1440 - 30) / 0.025;

  int upper_bits = (channel >> 8) | 0x40;
  int lower_bits = channel & 0xff;

  i2c_send(0x02, upper_bits);
  i2c_send(0x03, lower_bits);
}

void loop() {
  // put your main code here, to run repeatedly:
}

void i2c_send(int addr, int value){
	Wire.beginTransmission(dev_addr);
	Wire.write(addr);
	Wire.write(value);
	Wire.endTransmission();
	delay(3);
}

int i2c_read(int addr){
	Wire.beginTransmission(dev_addr);
	Wire.write(addr);
	Wire.endTransmission();
	Wire.requestFrom(dev_addr, 8);
	return Wire.read();
}