#define START_CMD_CHAR '*'
#define END_CMD_CHAR '#'
#define DIV_CMD_CHAR '|'
#define CMD_DIGITALWRITE 10
#define CMD_ANALOGWRITE 11
#define CMD_TEXT 12
#define CMD_READ_ARDUDROID 13
#define MAX_COMMAND 20 
#define MIN_COMMAND 10 
#define IN_STRING_LENGHT 40
#define MAX_ANALOGWRITE 255
#define PIN_HIGH 3
#define PIN_LOW 2

String inText;

void setup() {
  Serial.begin(9600);
  Serial.println("ArduDroid 0.12 Alpha by TechBitar (2013)");
  Serial.flush();
}

void loop()
{
  Serial.flush();
  int ard_command = 0;
  int pin_num = 0;
  int pin_value = 0;

  char get_char = ' '; 

  if (Serial.available() < 1) return;

  get_char = Serial.read();
  if (get_char != START_CMD_CHAR) return;

  ard_command = Serial.parseInt();
    
  pin_num = Serial.parseInt();
  pin_value = Serial.parseInt();

  if (ard_command == CMD_TEXT){   
    inText ="";
    while (Serial.available())  {
      char c = Serial.read(); 
      delay(5);
      if (c == END_CMD_CHAR) {
        break;
      }              
      else {
        if (c !=  DIV_CMD_CHAR) {
          inText += c; 
          delay(5);
        }
      }
    }
  }
  
  if (ard_command == CMD_DIGITALWRITE){  
    if (pin_value == PIN_LOW) pin_value = LOW;
    else if (pin_value == PIN_HIGH) pin_value = HIGH;
    else return;
    set_digitalwrite( pin_num,  pin_value);
    return;
  }

  if (ard_command == CMD_ANALOGWRITE) {  
    analogWrite(  pin_num, pin_value ); 
    return;
  }

  if (ard_command == CMD_READ_ARDUDROID) { 
    Serial.print(" Analog 0 = "); 
    Serial.println(analogRead(A0));
    return;  
  }
}

void set_digitalwrite(int pin_num, int pin_value)
{
  switch (pin_num) {
  case 13:
    pinMode(13, OUTPUT);
    digitalWrite(13, pin_value);  
    break;
  case 12:
    pinMode(12, OUTPUT);
    digitalWrite(12, pin_value);   
    break;
  case 11:
    pinMode(11, OUTPUT);
    digitalWrite(11, pin_value);         
    break;
  case 10:
    pinMode(10, OUTPUT);
    digitalWrite(10, pin_value);         
    break;
  case 9:
    pinMode(9, OUTPUT);
    digitalWrite(9, pin_value);         
    break;
  case 8:
    pinMode(8, OUTPUT);
    digitalWrite(8, pin_value);         
    break;
  case 7:
    pinMode(7, OUTPUT);
    digitalWrite(7, pin_value);         
    break;
  case 6:
    pinMode(6, OUTPUT);
    digitalWrite(6, pin_value);         
    break;
  case 5:
    pinMode(5, OUTPUT);
    digitalWrite(5, pin_value); 
    break;
  case 4:
    pinMode(4, OUTPUT);
    digitalWrite(4, pin_value);         
    break;
  case 3:
    pinMode(3, OUTPUT);
    digitalWrite(3, pin_value);         
    break;
  case 2:
    pinMode(2, OUTPUT);
    digitalWrite(2, pin_value); 
    break;      
  } 
}

