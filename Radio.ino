
//データシートを参考にしよう！
//http://aitendo3.sakura.ne.jp/aitendo_data/product_img/radio/dsp/m_pcb/m6951/M6951_dshver20130625.pdf

#include <Wire.h>

#define DEFAULT_SETTING 0b10100000 //on, am, no-seek, no-seekup, no-mute, rsv, rsv

//ボタン定義群
#define changeWave_Btn 2
#define changeHz_upper_Btn 3
#define changeHz_lower_Btn 4
#define volume_upper 5
#define volume_lower 6



void initPort();
void i2c_send(int addr, int value);
int i2c_read(int addr);
void setFMBand(int MHz);
void setAMBand(int KHz);

const int dev_addr = 0x10; //M6951のデバイスIDらしい・・・

void setup() {
  Serial.begin(9600);
  Serial.print(F("Debug Print\r\n"));	

  initPort();

  Wire.begin();
  i2c_send(0x00, DEFAULT_SETTING);
  i2c_send(0x01, 0b00001000);//AM(520-1710KHz, 5KHz Step)
  i2c_send(0x09, 0b00001111);//volume can control by I2C

  i2c_send(0x06, 0b10110101);//Volume(45)

  delay(10);

  setAMBand(1440);
}

void loop() {
	if(digitalRead(changeHz_lower_Btn)){

	}else if(digitalRead(changeHz_upper_Btn)){

	}else if(digitalRead(changeHz_lower_Btn)){

	}else if(digitalRead(volume_upper)){

	}else if(digitalRead(volume_lower)){

	}


	delay(1);
}

void initPort(){
	pinMode(changeWave_Btn, INPUT);
	pinMode(changeHz_upper_Btn, INPUT);
	pinMode(changeHz_lower_Btn, INPUT);
	pinMode(volume_upper, INPUT);
	pinMode(volume_lower, INPUT);
}

void i2c_send(int addr, int value) {
  Wire.beginTransmission(dev_addr);
  Wire.write(addr);
  Wire.write(value);
  Wire.endTransmission();
  delay(3);
}

int i2c_read(int addr) {
  Wire.beginTransmission(dev_addr);
  Wire.write(addr);
  Wire.endTransmission();
  Wire.requestFrom(dev_addr, 8);
  return Wire.read();
}


/*if you want to set band to 76.5MHz -> setFMBand(765);*/
void setFMBand(int MHz){
  int channel = (MHz - 300) * 4;
  int upper_bits = (channel >> 8) | 0x40;
  int lower_bits = channel & 0xff;

  i2c_send(0x02, upper_bits);
  i2c_send(0x03, lower_bits);
}

void setAMBand(int KHz){
  int channel = KHz/3;
  int upper_bits = (channel >> 8) | 0x60;
  int lower_bits = channel & 0xff;

  i2c_send(0x02, upper_bits);
  i2c_send(0x03, lower_bits);
}
