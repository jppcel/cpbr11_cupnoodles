/*********************************************************************
This is an example for our Monochrome OLEDs based on SSD1306 drivers

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98

This example is for a 128x64 size display using I2C to communicate
3 pins are required to interface (2 I2C and one reset)

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.  
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution

Code edited by Andrew R. from HobbyTransform for this example.
*********************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define XPOS 0
#define YPOS 1

#define ANALOG_X A0
#define ANALOG_Y A1
#define ANALOG_Z A2

#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 
static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x39,
0x3F, 0x3F, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x0F, 0x3F, 0x3F, 0x3F, 0x38, 0x00,
0x00, 0x00, 0x00, 0x00, 0x30, 0x06, 0x01, 0x02, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x01, 0x23,
0x22, 0x03, 0x07, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x01, 0x06, 0x11, 0x07, 0x27, 0x07, 0x06,
0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x11, 0x07, 0x27, 0x07, 0x02, 0x00, 0x00, 0x00, 0x00, 0x02,
0x04, 0x23, 0x07, 0x27, 0x07, 0x06, 0x00, 0x00, 0x00, 0x00, 0x02, 0x06, 0x03, 0x07, 0x27, 0x07,
0x04, 0x00, 0x00, 0x00, 0x00, 0x02, 0x07, 0x07, 0x07, 0x27, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x00,
0x02, 0x07, 0x3F, 0x07, 0x27, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x3F, 0x07, 0x23,
0x07, 0x30, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x39, 0x07, 0x27, 0x04, 0x00, 0x00, 0x00, 0x00,
0x00, 0x01, 0x20, 0x01, 0x03, 0x06, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x03, 0x20,
0x0E, 0x02, 0x00, 0x00, 0x00, 0x0F, 0x2F, 0x33, 0x3C, 0x0F, 0x30, 0x1E, 0x07, 0x3F, 0x2F, 0x38,
0x08, 0x38, 0x1E, 0x07, 0x21, 0x38, 0x0E, 0x06, 0x00, 0x18, 0x08, 0x08, 0x18, 0x18, 0x02, 0x00,
0x10, 0x06, 0x00, 0x00, 0x10, 0x0C, 0x0C, 0x0C, 0x30, 0x20, 0x08, 0x01, 0x22, 0x07, 0x04, 0x03,
0x04, 0x04, 0x0C, 0x21, 0x30, 0x1C, 0x01, 0x31, 0x07, 0x07, 0x03, 0x24, 0x04, 0x04, 0x20, 0x18,
0x06, 0x01, 0x30, 0x07, 0x04, 0x21, 0x34, 0x05, 0x04, 0x20, 0x18, 0x06, 0x01, 0x38, 0x07, 0x00,
0x30, 0x1C, 0x04, 0x22, 0x02, 0x30, 0x2F, 0x01, 0x38, 0x07, 0x00, 0x10, 0x04, 0x04, 0x20, 0x03,
0x30, 0x3F, 0x01, 0x38, 0x07, 0x06, 0x1C, 0x06, 0x04, 0x30, 0x23, 0x38, 0x3F, 0x01, 0x38, 0x07,
0x07, 0x33, 0x02, 0x05, 0x30, 0x21, 0x38, 0x1F, 0x01, 0x31, 0x07, 0x07, 0x31, 0x22, 0x0C, 0x38,
0x21, 0x38, 0x1E, 0x01, 0x31, 0x06, 0x07, 0x03, 0x22, 0x18, 0x38, 0x30, 0x38, 0x0E, 0x01, 0x23,
0x04, 0x06, 0x03, 0x22, 0x10, 0x1C, 0x18, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x10, 0x04, 0x14,
0x37, 0x3E, 0x07, 0x21, 0x20, 0x1E, 0x32, 0x20, 0x1C, 0x1C, 0x0F, 0x21, 0x23, 0x3C, 0x3F, 0x1F,
0x21, 0x3F, 0x3F, 0x37, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

char incomingByte;
int lines = 0;
int chars = 0;

int code[4];
int actualCode = 0;

void setup()   {              
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x64)
  // init done
  
  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(2000);

  // Clear the buffer.
  display.clearDisplay();

  display.setTextSize(4);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("----");
  display.display();

  // draw a bitmap icon and 'animate' movement
  //movingbitmap(logo16_glcd_bmp, LOGO16_GLCD_HEIGHT, LOGO16_GLCD_WIDTH);
  //Pinos ligados aos pinos 4, 5, 6 e 7 do teclado - Linhas
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
   
  //Pinos ligados aos pinos 8, 9, e 10 do teclado - Colunas
  pinMode(8, INPUT);
  //Ativacao resistor pull-up
  digitalWrite(8, HIGH);
  pinMode(9, INPUT);
  digitalWrite(9, HIGH);
  pinMode(10, INPUT);
  digitalWrite(10, HIGH);
   
  Serial.begin(9600);
  Serial.println("Teclado 4x3 - Exemplo 1");
  Serial.println("Aguardando acionamento das teclas...");
  Serial.println();
}


void loop()
{
    for (int porta = 4; porta<8; porta++)
    {
      //Alterna o estado dos pinos das linhas
      digitalWrite(4, HIGH);
      digitalWrite(5, HIGH);
      digitalWrite(6, HIGH);
      digitalWrite(7, HIGH);
      digitalWrite(porta, LOW);
      //Verifica se alguma tecla da coluna 1 foi pressionada
      if (digitalRead(8) == LOW)
      {
        imprime_linha_coluna(porta-3, 1);
        while(digitalRead(8) == LOW){}
      }
  
      //Verifica se alguma tecla da coluna 2 foi pressionada    
      if (digitalRead(9) == LOW)
      {
        imprime_linha_coluna(porta-3, 2);
        while(digitalRead(9) == LOW){};
      }
     
      //Verifica se alguma tecla da coluna 3 foi pressionada
      if (digitalRead(10) == LOW)
      {
        imprime_linha_coluna(porta-3, 3);
        while(digitalRead(10) == LOW){}
      }
    }
    
   delay(10);
 }
 
void imprime_linha_coluna(int x, int y)
{
  if(x == 1){
    switch(y){
      case 1:
        code[actualCode++] = 1;
        break;
      case 2:
        code[actualCode++] = 2;
        break;
      case 3:
        code[actualCode++] = 3;
        break;
    }
  } else 
  if(x == 2){
    switch(y){
      case 1:
        code[actualCode++] = 4;
        break;
      case 2:
        code[actualCode++] = 5;
        break;
      case 3:
        code[actualCode++] = 6;
        break;
    }
  }else 
  if(x == 3){
    switch(y){
      case 1:
        code[actualCode++] = 7;
        break;
      case 2:
        code[actualCode++] = 8;
        break;
      case 3:
        code[actualCode++] = 9;
        break;
    }
  } else
  if(x == 4){
    switch(y){
      case 1:
        
        break;
      case 2:
        code[actualCode++] = 0;
        break;
      case 3:
        
        break;
    }
  }
  Serial.println(code[0]);
  Serial.println(code[1]);
  Serial.println(code[2]);
  Serial.println(code[3]);  


    display.clearDisplay();
    display.setTextSize(4);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    switch(actualCode){
      case 0:
        display.print("----");
        break;
      case 4:
        display.print("*");
        Serial.print("*");
      case 3:
        display.print("*");
        Serial.print("*");
      case 2:
        display.print("*");
        Serial.print("*");
      case 1:
        display.print("*");
        Serial.print("*");
        break;
      default:
        display.println("----");
    }
    display.display();
  
  delay(1000);
  Serial.println();
  
}
