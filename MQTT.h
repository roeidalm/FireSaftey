
class MQTT
{
  public:
    MQTT(char server[], int port, char clientID[]);
    void MQTTOut();
    void setup_wifi();
    //void callback(char *topic, byte *payload, unsigned int length);
    void reconnect();
    bool connected();
    void clientloop();

  private:
    void callback(char *topic, byte *payload, unsigned int length);
};
