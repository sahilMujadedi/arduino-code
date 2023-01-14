const int RED_LED = 5;
const int GREEN_LED = 6;
const int BLUE_LED = 7;
const int SPEED = 1;

int RGB[3] = {0, 0, 0};

int colorRed[3] = {255, 0, 0};
int colorOrange[3] = {255, 120, 0}; 
int colorYellow[3] = {255, 255, 0};
int colorLime[3] = {119, 255, 0};
int colorGreen[3] = {0, 255, 0};
int colorTurquoise[3] = {0, 255, 120};
int colorCyan[3] = {0, 255, 255};
int colorOcean[3] = {0, 120, 255};
int colorBlue[3] = {0, 0, 255};
int colorViolet[3] = {120, 0, 255};
int colorMagenta[3] = {255, 0, 255};
int colorRedMagenta[3] = {255, 0, 120};

void setup() {
  // put your setup code here, to run once:
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  Serial.begin(9600);
  colorToColor(colorRed, colorOrange);
  

  
}

void loop() {
  // put your main code here, to run repeatedly:
    colorToColor(colorRedMagenta, colorRed);

    colorToColor(colorOrange, colorYellow);
  
    colorToColor(colorYellow, colorLime);
    
    colorToColor(colorLime, colorGreen);
    
    colorToColor(colorGreen, colorTurquoise);
    
    colorToColor(colorTurquoise, colorCyan);
    
    colorToColor(colorCyan, colorOcean);
    
    colorToColor(colorOcean, colorBlue);
    
    colorToColor(colorBlue, colorViolet);
    
    colorToColor(colorViolet, colorMagenta);
    
    colorToColor(colorMagenta, colorRedMagenta);
    
    colorToColor(colorRedMagenta, colorRed);
}

void setColor(int color[]) {
  analogWrite(RED_LED, color[0]);
  analogWrite(GREEN_LED, color[1]);
  analogWrite(BLUE_LED, color[2]);
}
void colorToColor(int color1[], int color2[]) {
  int distinct;
  
  for (int i = 0; i <= 2; i++) {
    
    if (color1[i] != color2[i]) {
      distinct = i;
    } else {
      RGB[i] = color1[i];
    }
    if (color1[distinct] > color2[distinct]) {

      for (int j = 0; j <= (color1[distinct] - color2[distinct]) / (SPEED); j++) {
        RGB[distinct] = (color2[distinct]) + (SPEED * j);
        setColor(RGB);
        
      }
    } else if (color1[distinct] < color2[distinct]) {

      for (int k = 0; k <= (color1[distinct] + color2[distinct]) / (SPEED); k++) {
        RGB[distinct] = (color1[distinct]) + (SPEED * k);
        setColor(RGB);
        
      }
    }
    
  }
  Serial.println(RGB[0]);
  Serial.println(RGB[1]);
  Serial.println(RGB[2]);
  Serial.println(distinct);
}