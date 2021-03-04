#include <Wire.h>
#include <MCP3427.h>

MCP3427 adcBoard;
byte fail = 0;

TwoWire* twi = &Wire;

void setup() {
  Serial.begin(115200);
  while(!Serial);
  twi->begin();
  
  // put your setup code here, to run once:
  adcBoard.begin(*twi);
}

byte enumerateI2C(TwoWire* WireInterface, boolean showErrors)
{
  byte addr, stat, last_ack = 0x00;
 
  Serial.print("Enumerating all I2C devices\n (Press any key to stop scanning I2C bus)\n-------------\n");
 
  for(addr=0x00; addr<0x7F; addr++)
  {
    WireInterface->beginTransmission(addr);
    stat = WireInterface->endTransmission();
    if(stat)
    {
      if(showErrors)
      {
        Serial.print("0x");
        Serial.print(addr, HEX);
        Serial.print(": ");
        Serial.print(stat);
        Serial.print("\n");
      }
    }  
    else
    {   
      Serial.print("0x");
      Serial.print(addr, HEX);
      Serial.print(" ");
      last_ack = addr;   
    }
  }  
  Serial.print("\n");
  return last_ack;
}

void loop() {
  bool result = false;
  int i = 0;
  // put your main code here, to run repeatedly:
  Serial.print("\n\n\nMCP3427 Test Program\n");
  Serial.println("------------------------\n");
 
  Serial.print("Bridge JP0H (addr=0x6D)");
  
  i = 0;
  do{
    i2cGeneralCallReset(twi);
    result = findI2CSlave(twi, 0x6D);
    Serial.print(".");
    if (++i >= 60)
    {
      Serial.print("\n");
      i=0;
    }
    delay(100);
  } while(!result);
  testResult(result);
  Serial.println("------------------------\n");
  
  Serial.print("Bridge JP1H (addr=0x6F)... ");
  i = 0;
  do{
    i2cGeneralCallReset(twi);
    result = findI2CSlave(twi, 0x6F);
    Serial.print(".");
    if (++i >= 60)
    {
      Serial.print("\n");
      i=0;
    }
    delay(100);
  } while(!result);
  testResult(result);

  Serial.println("------------------------\n");
  
  Serial.print("All jumpers open (addr=0x68)... ");

  i = 0;
  do{
    i2cGeneralCallReset(twi);
    result = findI2CSlave(twi, 0x68);
    Serial.print(".");
    if (++i >= 60)
    {
      Serial.print("\n");
      i=0;
    }
    delay(100);
  } while(!result);
  testResult(result);

  Serial.println("------------------------\n");

  do
  {
    float ch0Voltage = adcBoard.analogReadVoltage(0);
    float ch1Voltage = adcBoard.analogReadVoltage(1);
    Serial.print("Channel 0: ");
    Serial.print(ch0Voltage, 4);
    Serial.print("V (acceptable 1.09V to 1.11V)\n");
  
    Serial.print("Channel 1: ");
    Serial.print(ch1Voltage, 4);
    Serial.print("V (acceptable -1.09V to -1.11V)\n\n\n");

    if (ch0Voltage > 1.09 && ch0Voltage < 1.11 && ch1Voltage < -1.09 && ch1Voltage > -1.11)
      result = true;
    else
    {
      result = false;
      delay(250);
    }
    
    
    
  } while(!result);
  testResult(result);
}

void testResult(byte result)
{
  if(result)
  {
    Serial.println("Pass!");
  }
  else
  {
    Serial.println("*** Fail ***");
    fail = 1;
  }
}

byte i2cGeneralCallReset(TwoWire* WireInterface)
{
  byte stat=0;
  WireInterface->beginTransmission(0x00);
  WireInterface->write(0x06);  // RESET
  stat = WireInterface->endTransmission();
  return (!stat);
}


byte findI2CSlave(TwoWire* WireInterface, uint8_t addr)
{
  byte stat, done = 0;
  WireInterface->beginTransmission(addr);
  stat = WireInterface->endTransmission();
  return(!stat);
}
