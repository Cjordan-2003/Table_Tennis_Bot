
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Button.h>
#include <Servo.h>

Servo myservo;
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 20 chars and 4 line display
Button buttonRED(12);
Button buttonBLU(11);
Button buttonGRN(13);
Button buttonBLK(2);
Button buttonYLW(6);

int enA = 9;
int in1 = 8;
int in2 = 7;

int enB = 3;
int in3 = 5;
int in4 = 4;

bool BLK_state = false;
int speed = 8;
int spin_value = 0;
int ball_freq = 8;
int mode_value = 1;

void Motor_Speed(int speed_value, int spin)
{

  if (spin  < 0)
  {
     analogWrite(enA, (speed_value * 16) - (spin * 16));
    analogWrite(enB, speed_value * 16);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }
  else if (spin >= 0)
  {
    analogWrite(enA, speed_value * 16);
    analogWrite(enB, (speed_value * 16) - (spin * 16));
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }
}

void Servo_Motor(int ball)
{
 myservo.write(ball);
 //delay(250)

 //or maybe
 //myservo.write(tuned angle);
 //delay(ball)
}


void Display_Change(int mde, int val)
{
  lcd.clear();
  lcd.setCursor(0,0);
  String to_print = "";
  switch(mde)
  {
    String to_Print = "";
    case 1:
        to_print = "Speed\n" + String(val);
    case 2:
      to_print = "Spin\n" + String(val);
    case 3:
      to_print = "Ball Frequency\n" + String(val);
  }
  lcd.print(to_print);
}

void setup()
{
  myservo.attach(10);
  lcd.init();
  buttonRED.begin();
  buttonBLU.begin();
  buttonGRN.begin();
  buttonYLW.begin();
  buttonBLK.begin();
  lcd.backlight();
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

}
//mode yellow blue
//value red green

void loop()
{
if (buttonBLK.pressed())
{
  BLK_state = !BLK_state;
  if(BLK_state)
  {
    Motor_Speed(speed, spin_value);
    Servo_Motor(ball_freq);
  }
  else
  {
    Motor_Speed(0, 0);
    Servo_Motor(0);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, HIGH);
  }
}
if (buttonYLW.pressed())
{
  if (mode_value > 1)
  {
    --mode_value;
  }
}
if (buttonBLU.pressed())
{
  if (mode_value < 3)
  {
    ++mode_value;
  }
}
if (buttonRED.pressed())
{
  switch(mode_value)
  {
    case 1:
      if (speed > 0)
      {
        --speed;
      }
      break;
    case 2:
      if (spin_value > -16)
      {
        spin_value--;
      }
      break;
    case 3:
      if (ball_freq > 0)
      {
        ball_freq--;
      }
      break;
  }
}
if (buttonGRN.pressed())
{
  switch(mode_value)
  {
    case 1:
      if (speed < 16)
      {
        ++speed;
      }
      break;
    case 2:
      if (spin_value < 16)
      {
        spin_value++;
      }
      break;
    case 3:
      if (ball_freq < 16)
      {
        ball_freq++;
      }
      break;
  }
}
 /* switch(mode_value)
  {
    case 1:
    Display_Change(mode_value, speed);
    case 2:
    Display_Change(mode_value, spin_value);
    case 3:
    Display_Change(mode_value, ball_freq);
    default:
    lcd.print("failure \ndisplay_change");
  }
  */
    if(buttonGRN.pressed() || buttonYLW.pressed() || buttonRED.pressed() || buttonBLU.pressed())
    {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("M" + String(mode_value) + "  S" + String(speed) + "  SP" + String(spin_value) + "  BF" + String(ball_freq));
    }
  
}