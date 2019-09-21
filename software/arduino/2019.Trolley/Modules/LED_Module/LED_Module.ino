#include <Wire.h>

#define RED_LED 6
#define GREEN_LED 5

#define ADDR_PIN_0 2
#define ADDR_PIN_1 3
#define ADDR_PIN_2 4
#define ADDR_PIN_3 9

uint8_t ADDR_0 = 0x01;
uint8_t ADDR_1 = 0x02;
uint8_t ADDR_2 = 0x03;
uint8_t ADDR_3 = 0x04;

uint8_t CMD;

void green()
{
  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(RED_LED, LOW);
}

void red()
{
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, HIGH);
}

void yellow()
{
  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(RED_LED, HIGH);
}

void off()
{
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, LOW);
}


void error(String message)
{
  Serial.println("ERROR: " + message);
  while (true)
  {
    red()
    delay(1000);
    off()
    delay(1000);
  }
}

void info(String message)
{
  Serial.println("INFO: " + message);
}


uint8_t assignAddress()
{
  uint8_t address;
  bool selected = false;
  if (digitalRead(ADDR_PIN_0) == HIGH)
  {
    if (!selected)
    {
      address = ADDR_0;
      selected = true;
    }
    else
    {
      error("MULTIPLE ADDRESSES SELECTED");
    }
  }
  if (digitalRead(ADDR_PIN_1) == HIGH)
  {
    if (!selected)
    {
      address = ADDR_1;
      selected = true;
    }
    else
    {
      error("MULTIPLE ADDRESSES SELECTED");
    }
  }
  if (digitalRead(ADDR_PIN_2) == HIGH)
  {
    if (!selected)
    {
      address = ADDR_2;
      selected = true;
    }
    else
    {
      error("MULTIPLE ADDRESSES SELECTED");
    }
  }
  if (digitalRead(ADDR_PIN_3) == HIGH)
  {
    if (!selected)
    {
      address = ADDR_3;
      selected = true;
    }
    else
    {
      error("MULTIPLE ADDRESSES SELECTED");
    }
  }

  return address;
}



void setup() {
  pinMode(ADDR_PIN_0, INPUT_PULLUP);
  pinMode(ADDR_PIN_1, INPUT_PULLUP);
  pinMode(ADDR_PIN_2, INPUT_PULLUP);
  pinMode(ADDR_PIN_3, INPUT_PULLUP);

  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  
  yellow()

  Serial.begin(9600);

  randomSeed(analogRead(A0));

  Wire.begin(assignAddress());
  info("ADDRESS ASSIGNED");
  Wire.onReceive(receiveEvent); // register event
  Wire.onRequest(requestEvent);
}

void loop() {
  // put your main code here, to run repeatedly:

}

receiveEvent(int bytes)
{
  if(Wire.available() > 0)
  {
    CMD = Wire.receive();
  }
}

requestEvent()
{
  if (CMD == 0x01)
  {
    delay(random()); // Avoid Clashes
    Wire.write(0x01)

    info("RECEIVED PING FROM MASTER");
    green()
  }
}
