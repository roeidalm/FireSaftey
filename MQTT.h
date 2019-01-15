
class MQTT {
public:
MQTT();
void MQTTOut();
void setup_wifi();
void callback(char *topic, byte *payload, unsigned int length);
void reconnect();
bool connected();
void clientloop();
};
