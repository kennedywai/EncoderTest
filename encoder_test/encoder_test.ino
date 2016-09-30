/***MOTOR TEST***/
//Right Motor
int enA = 3;//analog
int in1 = 7;//digital
int in2 = 8;//digital
int encoderR_A = 2;//interrupt pin for right motor a
int encoderR_B = 4;//not using an interrupt pin for right motor B
//Left Motor
int enB = 4;//analog
int in3 = 9;//digital
int in4 = 10;//digital
int encoderL_A = 3;//interrupt pin for left motor a
int encoderL_B = 5;//not using an interrupt pin for left motor B

// variables to store the number of encoder pulses
// for each motor
volatile unsigned long rightCount = 0;
volatile unsigned long leftCount = 0;

void setup()
{
  // set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  
  // encoders
  pinMode(encoderR_A, INPUT);
  pinMode(encoderR_B, INPUT);
  pinMode(encoderL_A, INPUT);
  pinMode(encoderL_B, INPUT);
  
  // interrupts
  attachInterrupt(0, readEncoderR, CHANGE);
  attachInterrupt(1, readEncoderL, CHANGE);
  
  // 
  Serial.begin(9600);
  Serial.print("Start Counting");
}

void readEncoderR(){
if (digitalRead(encoderR_A) == HIGH) {
    if (digitalRead(encoderR_B) == LOW) {
      rightCount++;
    } else {
      rightCount--;
    }
  } else {
    if (digitalRead(encoderR_B) == LOW) {
      rightCount--;
    } else {
      rightCount++;
    }
  }
}

void readEncoderL(){
if (digitalRead(encoderL_A) == HIGH) {
    if (digitalRead(encoderL_B) == LOW) {
      leftCount++;
    } else {
      leftCount--;
    }
  } else {
    if (digitalRead(encoderL_B) == LOW) {
      leftCount--;
    } else {
      leftCount++;
    }
  }
}

void demoOne()
{
  // this function will run the motors in both directions at a fixed speed
  // turn on motor A
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  // set speed to 200 out of possible range 0~255
  analogWrite(enA, 200);
  // turn on motor B
  digitalWrite(in4, HIGH);
  digitalWrite(in3, LOW);
  // set speed to 200 out of possible range 0~255
  analogWrite(enB, 200);
  delay(2000);
  // now change motor directions
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);  
  digitalWrite(in4, LOW);
  digitalWrite(in3, HIGH); 
  delay(2000);
  // now turn off motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void demoTwo()
{
  // this function will run the motors across the range of possible speeds
  // note that maximum speed is determined by the motor itself and the operating voltage
  // the PWM values sent by analogWrite() are fractions of the maximum speed possible 
  // by your hardware
  // turn on motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH); 
  // accelerate from zero to maximum speed
  for (int i = 0; i < 256; i++)
  {
    analogWrite(enA, i);
    analogWrite(enB, i);
    delay(20);
  } 
  // decelerate from maximum speed to zero
  for (int i = 255; i >= 0; --i)
  {
    analogWrite(enA, i);
    analogWrite(enB, i);
    delay(20); 
    
  } 
  // now turn off motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);  
}
void loop()
{
  //demoOne();
  //Serial.print("Demo 1\n");
  //delay(1000);
  //demoTwo();
  //Serial.print("Demo 2\n");
  //delay(1000);
  
  Serial.print("Right Count:");
  Serial.println(rightCount);
  Serial.print("Left Count:");
  Serial.println(leftCount);
  delay(500);
}
