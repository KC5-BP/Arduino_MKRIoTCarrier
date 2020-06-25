
#include <Arduino_IOTSKcarrier.h>

IOTSKcarrier::IOTSKcarrier(){

}

int IOTSKcarrier::begin(){
    //Display
    display.init(240, 240);                // Initialize ST7789 screen
    pinMode(TFT_BACKLIGHT, OUTPUT);
    digitalWrite(TFT_BACKLIGHT, HIGH); // Backlight on
    
    //init LEDs
    leds.begin();
    

    //Sensors
    uint8_t sensorsOK = 0;

    if(!Light.begin()){
        sensorsOK |= 0b1 << 0;
    }
    if(!Preassure.begin()){
        sensorsOK |= 0b1 << 1;
    }
    if(!IMUmodule.begin()){
        sensorsOK |= 0b1 << 2;
    }
    if(!Env.begin()){
        sensorsOK |= 0b1 << 3;
    }

    //SD  card, not checkign the begin, if it doesnt have a SD plugged returns false
    SD.begin(SD_CS);

    Serial.println(sensorsOK,BIN);

    

    //If some of the sensors are not connected
    if(sensorsOK > 0){
        Serial.println("Error detected!");
        if(sensorsOK & 0b0001){
            Serial.println("Ambient light sensor is not connected!");
        }
        if(sensorsOK & 0b0010){
            Serial.println("Preassure sensor is not connected!");
        }
        if(sensorsOK & 0b0100){
            Serial.println("IMU is not connected");
        }
        if(sensorsOK & 0b1000){
            Serial.println("Environmental sensor is not connected!");
        }

       //while (true);
	   return false;
    }

    return true;
}