/*
Arduino LCD Keypad Shield 
modified on 21 Oct 2019
by Alireza Sheikhjafari @ Rabbit Channel
https://www.aparat.com/v/35zIX
*/
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
String commandString = "";


int EndOfCommend;
int EndOfdata;


void setup() {
 Serial.begin(9600); 
 initDisplay();
 pinMode(pin_BL, OUTPUT); 
 digitalWrite(pin_BL, HIGH); // sets the digital pin BL on
}
void loop() {
   if(Serial.available()) serialEvent();
  if(stringComplete)
  {
      stringComplete = false;
      getCommand();
      
      if(commandString.equals("Back_Light"))
      {
        String text = getData();
        if(text.equals("ON")){
          digitalWrite(pin_BL, HIGH); // sets the digital pin BL on
        }else if(text.equals("OFF"))
        {
           digitalWrite(pin_BL, LOW);  // sets the digital pin BL off          
        }
      }      
      else if(commandString.equals("LINE1"))
      {
        String text = getData();
        printText(text,1);
      }
       else if(commandString.equals("LINE2"))
      {
        String text = getData();
        printText(text,2);
      }
      else if(commandString.equals("CLEAR"))
      {
        lcd.clear();
      }
    inputString = "";
  }
  delay(100);
  
}



void initDisplay()
{
 lcd.begin(16, 2);
 lcd.setCursor(0,0);
 lcd.print("  Smart Rabbit ");
 lcd.setCursor(0,1);
 lcd.print("  Serial Port  ");
}



void getCommand()
{
  if(inputString.length()>0)
  {  
     EndOfCommend=inputString.indexOf(',');
     commandString = inputString.substring(1,EndOfCommend);
     Serial.println(commandString);
  }
}




String getData()
{
  String value = inputString.substring(EndOfCommend+1,inputString.length()-2);
  Serial.println(value);
  return value;
}

void printText(String text,int index)
{
  
    if(index==1)
    {
      lcd.setCursor(0,0);
      lcd.print(text);
    }else if(index==2)
    {
      lcd.setCursor(0,1);
      lcd.print(text);
    }
}

void serialEvent() {
  while (Serial.available() && stringComplete == false) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}

