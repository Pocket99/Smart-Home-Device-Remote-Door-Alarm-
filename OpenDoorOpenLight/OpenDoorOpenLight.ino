#include "MPU9250.h"

// an MPU9250 object with the MPU-9250 sensor on I2C bus 0 with address 0x68
MPU9250 IMU(Wire,0x68);
int status;
float gx_0 = 1;
float gx_1 = 1;
int LED = 13;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED,OUTPUT);
  
  
  Serial.begin(115200);
  while(!Serial) {}

  // start communication with IMU 
  status = IMU.begin();
  if (status < 0) {
    Serial.println("IMU initialization unsuccessful");
    Serial.println("Check IMU wiring or try cycling power");
    Serial.print("Status: ");
    Serial.println(status);
    while(1) {}
  }
  // setting the accelerometer full scale range to +/-8G 
  IMU.setAccelRange(MPU9250::ACCEL_RANGE_8G);
  // setting the gyroscope full scale range to +/-500 deg/s
  IMU.setGyroRange(MPU9250::GYRO_RANGE_500DPS);
  // setting DLPF bandwidth to 20 Hz
  IMU.setDlpfBandwidth(MPU9250::DLPF_BANDWIDTH_20HZ);
  // setting SRD to 19 for a 50 Hz update rate
  IMU.setSrd(19);

}

void loop() {
  // put your main code here, to run repeatedly:
  IMU.readSensor();
  //set current position
  gx_1 = IMU.getGyroX_rads();

  Serial.println("gx1 = :");
  Serial.println(gx_1);
  //check open / close action
  if(gx_1-gx_0>0.2||gx_0-gx_1>0.2){
      Serial.println("light");
      Serial.println(gx_0-gx_1);
    digitalWrite(LED,HIGH);
    delay(5000);
    gx_0 = gx_1;
  Serial.println("gx1 = :");
  Serial.println(gx_1);
  Serial.println("gx0 = :");
  Serial.println(gx_0);
  }
  else {
  digitalWrite(LED,LOW);
  delay(500);
  Serial.println("no light");
  Serial.println(gx_0-gx_1);
  }
  
}
