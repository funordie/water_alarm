#define PIN 10
#define VAL_PROBE 0

#define ADC_MAX 1023
#define WATER 500
//The setup function is called once at startup of the sketch
void setup()
{
// Add your initialization code here
    Serial.begin(115200);
    pinMode(PIN, OUTPUT);
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

    uint8_t state = 0;
    if(water >= WATER) state = 1;

    digitalWrite(PIN, state);

    delay(1000);
}

