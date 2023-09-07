# Temperature_Controlled_Fan_System_using_2MCUs
* Temperature Controls the Fan speed ,the lights and the machine
* First MUC reads the state from EEPROM and the temperature from temperature sensor then send them to the other MUC. 

### We have 2 states:
#### 1.Normal state:
* Machine is on
* Buzzer is OFF
* If temperature is less than 20 --> Fan is off and Green light is on
* If temperature is greater than 20 and less than 30 --> Fan is on and Green light is on
* If tempreature is greater than 30 and less than 40 --> Fan is on and Yellow light is on
* If tempreature is greater than 40 and less than 50 --> Fan is on with its maximum speed and Yellow Red light is on
* If temperature is greater than 50 --> Emergy state

#### 2.Emergy state: 
* Fan is ON with its Maximum speed
* Red Led is ON
* Buzzer is ON
* Machine is OFF

![WhatsApp Image 2023-09-07 at 14 09 38](https://github.com/BassantAhmedElbakry/Temperature_Controlled_Fan_System_using_2MCUs/assets/104600321/9bfd3b15-b11d-4c16-80c1-1ea2fa5222a9)
