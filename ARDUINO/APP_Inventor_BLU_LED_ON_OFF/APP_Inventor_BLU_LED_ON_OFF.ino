/*
Arduino LCD Keypad Shield 
modified on 21 Oct 2019
by Alireza Sheikhjafari @ Rabbit Channel
https://www.aparat.com/v/35zIX
*/
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
String commandString = "";
const int pin_LED = 10; 

int EndOfCommend;
int EndOfdata;


void setup() {
 Serial.begin(9600); 
 pinMode(pin_LED,OUTPUT);
}
void loop() {
   if(Serial.available()) serialEvent();
  if(stringComplete)
  {
      stringComplete = false;
      getCommand();
      
      if(commandString.equals("LED"))
      {
        String text = getData();
        if(text.equals("ON")){
         digitalWrite(pin_LED,HIGH);
        }else if(text.equals("OFF"))
        {
         digitalWrite(pin_LED,LOW);        
        }
      }      
     
    inputString = "";
  }
  delay(100);
  
}






void getCommand()
{
  if(inputString.length()>0)
  {  
     EndOfCommend=inputString.indexOf(',');
     commandString = inputString.substring(1,EndOfCommend);
     
     Serial.print("Command:");
     Serial.println(commandString);
  }
}




String getData()
{
  String value = inputString.substring(EndOfCommend+1,inputString.length()-2);
  Serial.print("Data:");
  Serial.println(value);
  Serial.println("---------------------------");
  return value;
}



void serialEvent() {
  while (Serial.available() && stringComplete == false) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    Serial.print(inChar);
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}

