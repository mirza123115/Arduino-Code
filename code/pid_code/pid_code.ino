#include "defs.h"

uint8_t check_sensor()
{
  uint8_t outn=0;
  return ((digitalRead(S3)<<3)+(digitalRead(S2)<<2)+(digitalRead(S1)<<1)+(digitalRead(S0)<<0));
}


void initialize_io()
{
  pinMode(IN1_IO,OUTPUT);
  pinMode(IN2_IO,OUTPUT);
  pinMode(IN3_IO,OUTPUT);
  pinMode(IN4_IO,OUTPUT);
}
void run_motor(uint8_t pwm_left,bool direction_left,uint8_t pwm_right,bool direction_right)
{
  if(direction_left==true)
  {
    digitalWrite(IN1_IO,HIGH);
    digitalWrite(IN2_IO,LOW);
  }
  else
  {
    digitalWrite(IN1_IO,LOW);
    digitalWrite(IN2_IO,HIGH);
  }

  if(direction_right==true)
  {
    digitalWrite(IN3_IO,HIGH);
    digitalWrite(IN4_IO,LOW);
  }
  else
  {
    digitalWrite(IN3_IO,LOW);
    digitalWrite(IN4_IO,HIGH);
  }
  analogWrite(PWM_LEFT_IO,pwm_left);
  analogWrite(PWM_RIGHT_IO,pwm_right);
}


int8_t get_sensor_reading()
{
  uint8_t sensor_raw_data=check_sensor();
  if(sensor_raw_data==0b00001000)
  {
    return -5;
  }
  else if(sensor_raw_data==0b00001100||sensor_raw_data==0b00001010)
  {
    return -4;
  }
  else if(sensor_raw_data==0b00000100)
  {
    return -3;
  }
  else if(sensor_raw_data==0b00000110)
  {
    return 0;
  }
  else if(sensor_raw_data==0b00000010)
  {
    return 3;
  }
  else if(sensor_raw_data==0b00000011||sensor_raw_data==0b00000101)
  {
    return 4;
  }
  else if(sensor_raw_data==0b00000001)
  {
    return 5;
  }
  else if(sensor_raw_data==0b00000000)
  {
    return last_sensorval;
  }
  else
  {
    return 0;
  }
}

int calculate_pid(int8_t sensor_data)
{
  //this function calculates the correction value
  int8_t error=0;
  double kp_val=0.0;
  double ki_val=0.0;
  double kd_val=0.0;
  double pid_corr=0.0;
  int pid_corr_out=0;
  error=target_value-sensor_data;
  kp_val=Kp*(double(error));
  ki_val=Ki*double(error_acc);
  kd_val=kd*(double(error-lasterror));
  if(ki_val>ki_max)
  {
    ki_val=ki_max;
  }
  if(ki_val<-1*ki_max)
  {
    ki_val=-1*ki_max;
  }
  pid_corr=kp_val+ki_val+kd_val;
  pid_corr_out=int(pid_corr);
  error_acc+=error;
  lasterror-error;
  return pid_corr_out;
}

void setup() {
  Serial.begin(9600);
  initialize_io();
  delay(2000);
}

void loop() {
  int8_t sensor_data=0;
  int correction_value=0;
  int corrected_speed_left=0;
  int corrected_speed_right=0;
  //get sensor data
  sensor_data=get_sensor_reading();
  correction_value=calculate_pid(sensor_data);
  corrected_speed_left=base_spd_left-correction_value;
  corrected_speed_right=base_spd_right+correction_value;
  
  //some housekeeping
  if(corrected_speed_left>255)
  {
    corrected_speed_left=255;
  }
  
  if(corrected_speed_left<105)
  {
    corrected_speed_left=105;
  }


  if(corrected_speed_right>255)
  {
    corrected_speed_right=255;
  }
  
  if(corrected_speed_right<80)
  {
    corrected_speed_right=80;
  
  }
  Serial.print(sensor_data);
  Serial.print("\t");
  Serial.print(uint8_t(corrected_speed_left));
  Serial.print("\t");
  Serial.println(uint8_t(corrected_speed_right));
  
  run_motor(uint8_t(corrected_speed_left),FWD,uint8_t(corrected_speed_right),FWD);
  last_sensorval=sensor_data;
  delay(50);
}

