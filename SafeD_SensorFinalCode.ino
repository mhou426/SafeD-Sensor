//define the variables
#define redLED 4
#define yellowLED 5
#define greenLED 6
#define mainButton 9
#define fanButton 7
#define motorPin 13

//set boolean variables to be true or false
bool turnOn = false;
bool isReleased = true;
bool turnOnFan = false;
bool isReleasedFan = true;

//initialize the variables
int triggerPin = 2;
int echoPin = 3;
int buzzerPin = 10;

//initialize new variables to store data
int buttonState;
int buttonStateFan;

int pingTime;
unsigned long distance;/*make sure all values resulted
                         are positive*/

void setup(){
  // to set all variables to be either an INPUT or OUTPUTS
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);

  pinMode(mainButton, INPUT);
  pinMode(fanButton, INPUT);
  pinMode(motorPin, OUTPUT);
}

void loop(){
  digitalWrite (triggerPin, HIGH);//turn ON the triggerPin in the Ping sensor
  delayMicroseconds (10);//run the above function for 10 microseconds
  digitalWrite (triggerPin, LOW);//turn OFF the triggerPin in the Ping sensor
  
  //detects how long it takes the ultrasound to go and come back from the nearest object
  pingTime = pulseIn (echoPin, HIGH);
  //formula to convert the time that the ultrasound travels to its corresponding distance (d = vt)
  distance = (pingTime * 0.034) / 2;

  //read the status of the buttons to see whether it was pressed or not
  buttonState = digitalRead(mainButton);
  buttonStateFan = digitalRead(fanButton);

  if ((buttonState == HIGH) && (isReleased)){/*test for two conditions: 1)if the button is pressed 
                                              2)a true boolean variable to assist in the ON/OFF process*/
    //isReleased is used to individualize each button press
    isReleased = false;//temporarily sets this variable to be false
    delay(500);//run the above function for 0.5 seconds, just for a pause

    if (buttonState == HIGH){//set condition if the button is pressed
      turnOn = !turnOn;//this inverts the state of the variable once the button is pressed
    }
  }//close "if ((buttonState == HIGH) && (isReleased))"

  else if (buttonState == LOW){/*isReleased goes back to its original value after you let go of the button, 
                                enabling us to change the value of turnOn with the next button press*/
    isReleased = true;
  }

  if (turnOn){ //run the rest of the code if turnOn == true
    //DANGER ZONE
    if (distance < 182.88){ //182.88cm = 6ft, distance have to be less than 6ft
      digitalWrite(redLED, HIGH);//turn the redLED ON and other LEDs OFF
      digitalWrite(greenLED, LOW);
      digitalWrite(yellowLED, LOW);

      tone(buzzerPin, 200);//turn the buzzer ON
      delay(50);//run the above funtion for 0.05 seconds
    }//BE CAUTION
    else if((distance <= 213.36) && (distance >= 182.88)){ //213.36cm = 7ft,
    //condition will meet only when 6ft <= distance <= 7ft
      digitalWrite(yellowLED, HIGH);//turn the yellowLED ON and other LEDs OFF
      digitalWrite(greenLED, LOW);
      digitalWrite(redLED, LOW);
      
      noTone(buzzerPin);//turn the buzzer OFF
      delay(50);//run the above funtion for 0.05 seconds
    }//SAFE ZONE
    else{//any distance greater than 7ft
    digitalWrite(greenLED, HIGH);////turn the greenLED ON and other LEDs OFF
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, LOW);

    noTone(buzzerPin);//turn the buzzer OFF
    delay(50);//run the above funtion for 0.05 seconds
    }
  }//close "if (turnOn)"
  
  else{//when turnOn == false, none of the components will turn on
    digitalWrite(greenLED, LOW);//turn ALL LEDs OFF
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, LOW);

    noTone(buzzerPin);//turn the buzzer OFF
  }
  
//CODE FOR FAN - same set of codes used in the main circuit
  if ((buttonStateFan == HIGH) && (isReleasedFan)){
    isReleasedFan = false;
    delay(500);
    
    if (buttonStateFan == HIGH) {
      turnOnFan = !turnOnFan;
    }    
  }//close "if (buttonState == HIGH) && (isReleasedFan))"
  else if (buttonStateFan == LOW){
    isReleasedFan = true;
  }
  
  if (turnOnFan){
    digitalWrite(motorPin, HIGH);//turn the fan ON
  }
  else{
    digitalWrite(motorPin, LOW);//turn the fan OFF
  }

} //close "void loop()"

//first press:
//- isReleased = true - false - true
//- turnOn = false - true 

//second press:
//- isReleased = true - false - true
//- turnOn = true - false
