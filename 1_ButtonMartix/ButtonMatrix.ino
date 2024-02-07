int btn_pin_2 = 2;
int btn_pin_3 = 3;
int btn_pin_4 = 4;
int btn_pin_5 = 5;
int delay_time = 1000;
int buttons[] = {0, 0, 0, 0};

void setup()
{
    Serial.begin(9600);
    pinMode(btn_pin_2, OUTPUT);
    pinMode(btn_pin_3, OUTPUT);
    pinMode(btn_pin_4, INPUT_PULLUP);
    pinMode(btn_pin_5, INPUT_PULLUP);
}

void loop()
{
  //int current_time = millis();
  //if (current_time%(delay_time/2)==0){
  //  Serial.println();
  //  delay(delay_time);
  //}
    int pins[] = {2, 3};
    int states[] = {0, 1};
  
    digitalWrite(pins[0], states[0]);
    digitalWrite(pins[1], states[1]);
  	pin_read(btn_pin_4, 4);
  	pin_read(btn_pin_5, 2);
  
    digitalWrite(pins[0], !states[0]);
    digitalWrite(pins[1], !states[1]);
  	pin_read(btn_pin_4, 3);
  	pin_read(btn_pin_5, 1);
  
}

void pin_read(int pin, int btn_num){
  if (digitalRead(pin) == LOW){
    buttons[btn_num-1]=1;
    
   //for (int i=0; i<4; i++) {
   //    Serial.print(buttons[i]);	
    // }
  	Serial.println();
  	Serial.println();
   for (int i=0; i<4; i++) {
     bool one_btn = true;
     
     if (buttons[i]==1){
       
       for (int j=0; j<i; j++) {
         if ((buttons[j]==1) && (i!=j)){
           one_btn = false;
           Serial.print("Second button ");
           Serial.println(i+1);
         }
       }
       
       if (one_btn == true){
         Serial.print("Button ");
         Serial.println(i+1);
       }
       
     }
   }
    delay(delay_time);


  } else{
    buttons[btn_num-1]=0;
  }
}