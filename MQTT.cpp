
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include "config.h"
#include "sensorsAndTypes.h"
#include <Events.h>
#include <EventQueue.h>
#include <EventDispatcher.h>

#define MQTT_MAX_PACKET_SIZE 500 //dons't check it yet, but I think it will let you to send longer data to MQTT
WiFiClient espClient;
PubSubClient client(espClient);
EvtManager mgr;
USE_EVENTUALLY_LOOP(mgr);
client : public;
MQTT::MQTT()
{

    int sizeofBuffer = 15; //sizeofBuffer = (sizeof(int) * SMOKEpinsLength) + (sizeof(int) * SMOKEpinsLength) + 60;

    void MQTTOut()
    {
        if (!client.connected())
        {
            reconnect();
        }
        client.loop();
        sizeofBuffer = 500; //(sizeof(DHT) * SMOKEpinsLength) + (sizeof(int) * SMOKEpinsLength) + 60;

        DynamicJsonBuffer JSONbuffer;
        JsonObject &JSONencoder = JSONbuffer.createObject();
        JSONencoder["device"] = clientID;
        JSONencoder["fS"] = esp_get_free_heap_size();
        JsonArray &tempsStatus = JSONencoder.createNestedArray("t");
        JsonArray &humidsStatus = JSONencoder.createNestedArray("h");
        JsonArray &smokes = JSONencoder.createNestedArray("s");
        /*
    for (int i = 0; i < DHTpinsLength; i++)
    {
        if (temps[i] < 700)
        {
            tempsStatus.add(temps[i]);
        }
        else
        {
            tempsStatus.add(-1);
        }
        if (humids[i] < 700)
        {
            humidsStatus.add(humids[i]);
        }
        else
        {
            humidsStatus.add(-1);
        }
    };

    for (int i = 0; i < SMOKEpinsLength; i++)
    {
        smokes.add(SMOKESTATES[i]);
    };
    char JSONmessageBuffer[100];
    JSONencoder.printTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
    Serial.println("Sending message to MQTT topic..");
    Serial.println(JSONmessageBuffer);

    client.publish(OutTopic, JSONmessageBuffer);
    Serial.println("message Sent  to MQTT:");
    Serial.println("Topic: " + String(OutTopic));
    */
        delay(1000);
    }

    void setup_wifi()
    {
        digitalWrite(2, HIGH);
        delay(150);
        digitalWrite(2, LOW);
        delay(150);
        digitalWrite(2, HIGH);

        delay(1000);
        // We start by connecting to a WiFi network
        Serial.println();
        Serial.println("Setting WiFi ");
        WiFi.mode(WIFI_STA);
        Serial.println("Disconnetting WiFi ");
        WiFi.disconnect();
        delay(100);
        Serial.print("Connecting to ");
        Serial.println(ssid);
        WiFi.begin(ssid, password);

        while (WiFi.status() != WL_CONNECTED)
        {
            delay(1000);
            Serial.print(".");
            Serial.println(WiFi.localIP());
            Serial.print("Status: ");
            Serial.println(WiFi.status());
            digitalWrite(2, HIGH);
            delay(150);
            digitalWrite(2, LOW);
        }

        Serial.println("");
        Serial.println("WiFi connected");
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP());
        digitalWrite(2, HIGH);
        delay(500);
        digitalWrite(2, LOW);
    }

    void reconnect()
    {
        // Loop until we're reconnected
        int leaveWifi = 0;
        while (!client.connected() || leaveWifi > 10)
        {
            digitalWrite(2, HIGH);
            delay(500);
            digitalWrite(2, LOW);
            Serial.print("Attempting MQTT connection...");
            // Attempt to connect
            if (client.connect(clientID))
            {
                Serial.println("connected");
                client.subscribe(inTopic);
                Serial.println("Topic: " + String(inTopic));
            }
            else
            {
                client.setServer(mqtt_server, port);
                if (client.connect(clientID))
                {
                    Serial.println("connected");
                    client.subscribe(inTopic);
                }
                else
                {
                    Serial.print("failed, rc=");
                    Serial.print(client.state());
                    Serial.println(" try again in 5 seconds");
                }
            }
            leaveWifi = leaveWifi + 1;
            delay(2000);
        }
        digitalWrite(2, HIGH);
        delay(1000);
        digitalWrite(2, LOW);
        digitalWrite(2, HIGH);
        delay(50);
        digitalWrite(2, LOW);
    }
    bool connected()
    {
        return client.connected();
    }
    void clientloop()
    {
        client.loop();
    }
}
void MQTT::MQTT()
{

    //starting the wifi and the MQTT
    *mqtt->setup_wifi();
    client.setServer(mqtt_server, port);
    client.setCallback(*callback);
}
void callback(char *topic, byte *payload, unsigned int length)
{
    // Conver the incoming byte array to a string
    payload[length] = '\0'; // Null terminator used to terminate the char array
    char *message = (char *)payload;

    callbackmethod res = {topic, message};

}