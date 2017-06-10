#define PIN 10
#define VAL_PROBE 0

#define ADC_MAX 1023
#define WATER_LEVEL 500
#define ALARM_TIME_MS (10UL*60*1000)
//The setup function is called once at startup of the sketch
void setup()
{
// Add your initialization code here
    Serial.begin(115200);
    pinMode(PIN, OUTPUT);
}

void SetAlarm(bool newState) {
    static unsigned long ulStartTime = 0;
    static bool status = false;

    if(!status && newState) {
        //if alarm is not started and request is ON
        status = true;
        ulStartTime = millis();
        digitalWrite(PIN, true);
    }

    //check for alarm period
    unsigned long ulTime = millis();
    if(!newState || ((ulTime - ulStartTime) > ALARM_TIME_MS)) {
        //stop alarm
        digitalWrite(PIN, false);
    }


}

// The loop function is called in an endless loop
void loop()
{
//Add your repeated code here
    static uint8_t count = 0;
    count++;
    char buffer[20];
    sprintf(buffer, "Loop %d", count);
    Serial.println(buffer);

    uint16_t water = ADC_MAX - analogRead(VAL_PROBE);
    sprintf(buffer, "Water %d", water);
    Serial.println(buffer);

    SetAlarm(water >= WATER_LEVEL);

    delay(1000);
}

