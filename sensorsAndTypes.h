

//sensors

//Alerts:
int AlarmTemp = 48; // Alarm temp High Limit

//MQ2 PIN
int SMOKEPINS[] = {4};
int SMOKEpinsLength = sizeof(SMOKEPINS) / sizeof(SMOKEPINS[0]);

struct callbackmethod
{
    char *topic;
    char *payload;
};
