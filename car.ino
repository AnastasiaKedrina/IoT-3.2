#define FRONT_Trig 9
#define FRONT_Echo 8
#define LEFT_Trig 11
#define LEFT_Echo 10

#define SPEED_1      5 // RIGHT_SIDE 
#define DIR_1        4 // RIGHT_SIDE
#define SPEED_2      6 // LEFT_SIDE
#define DIR_2        7 // LEFT_SIDE

#define MIN_D        5 // min distance
#define MIN_FRONT_D        20 // min distance
#define MIN_LEFT_D        20 // min distance
#define time_delay   500 

long current_time = 0;
long rotation_time = 0;
long currentMillis = 0;
long heartbeatMillis = 0;

 
unsigned int FRONT_impulseTime = 0;
unsigned int LEFT_impulseTime = 0;
unsigned int front_distance = 0;
unsigned int left_distance = 0;

int car_speed = 120;

int rotation_90_time = car_speed*0.8;
int rotation_45_time = rotation_90_time/2;
int rotation_180_time = rotation_90_time*2;


void setup()
{
  Serial.begin (9600); 
  pinMode(FRONT_Trig, OUTPUT); 
  pinMode(FRONT_Echo, INPUT); 
  pinMode(LEFT_Trig, OUTPUT); 
  pinMode(LEFT_Echo, INPUT); 
  current_time = millis();
  rotation_time = millis();

  //save current time
  currentMillis = millis();


  for (int i = 4; i < 8; i++) {     
    pinMode(i, OUTPUT);
  }
}

void loop()
{

  //----------------------get distance
  digitalWrite(FRONT_Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(FRONT_Trig, LOW);
  FRONT_impulseTime = pulseIn(FRONT_Echo, HIGH);
  front_distance = FRONT_impulseTime/2 / 29.1; //to cm
  Serial.print("FRONT-");
  Serial.print(front_distance);
  Serial.print("----");
  delay(200);

  digitalWrite(LEFT_Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(LEFT_Trig, LOW);
  LEFT_impulseTime = pulseIn(LEFT_Echo, HIGH);
  left_distance = LEFT_impulseTime/2 / 29.1;
  Serial.print("LEFT-");
  Serial.println(left_distance);
  delay(200);
  

  //----------------------functions
  // move_forward(car_speed);
  // move_back(car_speed);
  // stop();

  // left_rotation(car_speed);
  // right_rotation(car_speed);
  // left_turn(car_speed, 0.5);
  // right_turn(car_speed, 0.5);

  states(); // all functions

}

void right_rotation(int car_speed) {
    digitalWrite(DIR_1, LOW);  
    digitalWrite(DIR_2, HIGH);
    analogWrite(SPEED_1, car_speed);  
    analogWrite(SPEED_2, car_speed);
}

void left_rotation(int car_speed) {
    digitalWrite(DIR_1, HIGH);  
    digitalWrite(DIR_2, LOW);
    analogWrite(SPEED_1, car_speed);  
    analogWrite(SPEED_2, car_speed);
}

void states(){  
 if (front_distance < MIN_FRONT_D && left_distance < MIN_LEFT_D){
  // спереди стена, слева стена - поворот направо
    right_rotation(car_speed);
  Serial.println("GO RIGHT");
    }
 else if (front_distance < MIN_FRONT_D && left_distance > MIN_LEFT_D){
  // спереди стена, слева пусто - поворот налево
    left_rotation(car_speed);
  Serial.println("DO LEFT");
 }
  
 else if (front_distance > MIN_FRONT_D && left_distance < MIN_LEFT_D){
  // спереди пусто, слева стена - ехать прямо
    move_forward(car_speed);
  Serial.println("FORWARD");
  }
  
 else if (front_distance > MIN_FRONT_D && left_distance > MIN_LEFT_D){
  // спереди пусто, слева пусто - поворот налево
    left_rotation(car_speed);
    delay(500);
    move_forward(car_speed);
    
  Serial.println("GO LEFT");
 }
  delay(500);
  stop();

void move_back(int car_speed) {
  digitalWrite(DIR_1, LOW);  
  digitalWrite(DIR_2, LOW);
  analogWrite(SPEED_1, car_speed);  
  analogWrite(SPEED_2, car_speed);
}

void move_forward(int car_speed) {
  digitalWrite(DIR_1, HIGH);  
  digitalWrite(DIR_2, HIGH);
  analogWrite(SPEED_1, car_speed);  
  analogWrite(SPEED_2, car_speed);
}

void stop(){
  analogWrite(SPEED_1, 0);  
  analogWrite(SPEED_2, 0);
}

void left_turn(int car_speed, float steepness) {
  if(steepness > 1) {
    steepness = 1;
  }
    if(steepness < 0) {
    steepness = 0;
  }
  digitalWrite(DIR_1, HIGH);  
  digitalWrite(DIR_2, LOW);
  analogWrite(SPEED_1, car_speed);  
  analogWrite(SPEED_2, car_speed * steepness);
}

void right_turn(int car_speed, float steepness) {
  if(steepness > 1) {
    steepness = 1;
  }
    if(steepness < 0) {
    steepness = 0;
  }
  digitalWrite(DIR_1, LOW);  
  digitalWrite(DIR_2, HIGH);
  analogWrite(SPEED_1, car_speed * steepness);  
  analogWrite(SPEED_2, car_speed);
}