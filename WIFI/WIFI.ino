#include <SoftwareSerial.h>
SoftwareSerial mySerial(3, 2); // RX, TX 配置 3、2 为软串口
void setup()
{
  Serial.begin(9600);
  Serial.println("ESP8266 WIFI Test");
  while (!Serial) {
    ;
  }
  Serial.println("hardware serial!");
  mySerial.begin(9600);
  mySerial.println("software seria");
}
void loop()
{
  if (mySerial.available())
  {
    Serial.write(mySerial.read());
  }
  if (Serial.available()) {
    mySerial.write(Serial.read());
  }
}
