#include "config.h"
#include "sensorsAndTypes.h"
#include "MQTT.h"
#include <ArduinoOTA.h>
#include <Eventually.h>



/*I take Main from config
const char ssid[]  = "XXX";
const char password[]  = "XXX";
const char mqtt_server[]  = "XXXX";
const int port = 1883;
const char clientID[]  = "RF2Bridge";
const char inTopic[] = "GateWayIn";
const char OutTopic[] = "GateWayOut";
const char complateOutTopic[] = "complateGateWayOut";
const char complateTopic[] = "GateWayComplate";
*/

MQTT *mqtt=new MQTT(mqtt_server, port,callback);

int LED = 13;
long arrayOfRfs[150];

char msg[50];
uint32_t FirstFreeSpeace = esp_get_free_heap_size();
unsigned long timer_last_keep_ALIVE = 0;

bool monitoring = false;


void setup()
{

    Serial.begin(115200);
    pinMode(LED, OUTPUT);

    

    timer_last_keep_ALIVE = millis() - 1800001;

    //OTA
    ArduinoOTA
        .onStart([]() {
            String type;
            if (ArduinoOTA.getCommand() == U_FLASH)
                type = "sketch";
            else // U_SPIFFS
                type = "filesystem";

            // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
            Serial.println("Start updating " + type);
        })
        .onEnd([]() {
            Serial.println("\nEnd");
        })
        .onProgress([](unsigned int progress, unsigned int total) {
            Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
        })
        .onError([](ota_error_t error) {
            Serial.printf("Error[%u]: ", error);
            if (error == OTA_AUTH_ERROR)
                Serial.println("Auth Failed");
            else if (error == OTA_BEGIN_ERROR)
                Serial.println("Begin Failed");
            else if (error == OTA_CONNECT_ERROR)
                Serial.println("Connect Failed");
            else if (error == OTA_RECEIVE_ERROR)
                Serial.println("Receive Failed");
            else if (error == OTA_END_ERROR)
                Serial.println("End Failed");
        });
    ArduinoOTA.setHostname(clientID);
    ArduinoOTA.begin();
}

void loop()
{

    ArduinoOTA.handle();

    if (!*mqtt->connected())
    {
        *mqtt->reconnect();
    }
    *mqtt->clientloop();

    
    if (monitoring)
    {
        TempFunctions(); //Do the temp related stuff
        SmokeFunction();
        Alarm(); //Activate alarm if applicable
        DebugMode();
        *mqtt->MQTTOut();
        delay(500);
    }
}

void TempFunctions()
{
    // READ array Temp
    for (int i = 0; i <150 ; i++)
    {       
    }
}
void SmokeFunction()
{
      // READ array SMOKE
        for (int i = 0; i < SMOKEpinsLength; i++)
    {
        
    }
}

void Alarm()
{    
    //checking the alarms
    /*
    for (int i = 0; i < SMOKEpinsLength; i++)
    {
        if (SMOKESTATES[i] == LOW)
        {
            Serial.println("System Note Fine!");
        }
    };*/
}

void DebugMode()
{
  /*  //temp:
    for (int i = 0; i < DHTpinsLength; i++)
    {
        Serial.print("Temperature ");
        Serial.print("i IS: ");
        Serial.print(i);
        Serial.print("\n");
        Serial.print(temps[i]);
        Serial.println(" *C");
        Serial.print("humid: ");
        Serial.println(humids[i]);
        delay(250);
    };

    //Smoke:
    for (int i = 0; i < SMOKEpinsLength; i++)
    {
        Serial.print("SMOKE ");
        Serial.print("i IS: ");
        Serial.print(i);
        Serial.print("\n");
        Serial.println(SMOKESTATES[i]);
    };*/
}




void eventmethod(){
        //SHUT DOWN ENTIRE SYSTEM!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        //SHUT DOWN ENTIRE SYSTEM!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        //SHUT DOWN ENTIRE SYSTEM!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        //SHUT DOWN ENTIRE SYSTEM!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        //SHUT DOWN ENTIRE SYSTEM!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        //SHUT DOWN ENTIRE SYSTEM!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        //SHUT DOWN ENTIRE SYSTEM!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

        StaticJsonBuffer<300> JSONbuffer;
        JsonObject &JSONencoder = JSONbuffer.createObject();
        JSONencoder["device"] = clientID;
        JSONencoder["freeSpeace"] = esp_get_free_heap_size();

        if (true)
        {
            JSONencoder["SeccsedStatus"] = true;
        }
        else
        {
            JSONencoder["SeccsedStatus"] = false;
        }

        char JSONmessageBuffer[100];
        JSONencoder.printTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
        Serial.println("Sending message to MQTT topic..");
        Serial.println(JSONmessageBuffer);

        client.publish(complateTopic, JSONmessageBuffer);

        Serial.println("Message Sent on topic: ");
        Serial.println(topic);
        Serial.println(message);

}