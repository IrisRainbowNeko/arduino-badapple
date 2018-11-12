
#include <SPI.h>
#include <SD.h>
#include <Wire.h>  
#include <Adafruit_GFX.h>  
#include <Adafruit_SSD1306.h>  
  
#define OLED_RESET 4  
Adafruit_SSD1306 display(OLED_RESET);  
  
#define LOGO16_GLCD_HEIGHT 16 //定义显示高度  
#define LOGO16_GLCD_WIDTH  16 //定义显示宽度  
    
#if (SSD1306_LCDHEIGHT != 64)  
#error("Height incorrect, please fix Adafruit_SSD1306.h!");  
#endif  

File myFile;

byte img[704];

void setup() {
  Serial.begin(9600);
  if (!SD.begin(4)) {//初始化SD卡模块
      Serial.println("initialization failed!");
      return;
    }
    Serial.println("initialization done.");//初始化结束

  myFile = SD.open("badapple.bin");//打开文件
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);//初始化oled屏
}

void loop() {
  display.clearDisplay();//刷新屏幕
  
  if (myFile) {
    myFile.read(img,704);//读取数据(每帧704字节)
  }

  display.drawBitmap(22, 0, img, 88, 64, 1);//绘制图像
  display.display();//显示已绘制的图像
}


