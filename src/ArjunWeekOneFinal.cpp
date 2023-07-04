/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/student/Desktop/IoT/ArjunWeekOneFinal/src/ArjunWeekOneFinal.ino"
#include "env.h"
#include "Wire.h"
#include "blynk.h"
#include "oled-wing-adafruit.h"
#include "SparkFun_VCNL4040_Arduino_Library.h"

void setup();
void loop();
void ResetDisplay();
void LowValue();
void HighValue();
#line 7 "/Users/student/Desktop/IoT/ArjunWeekOneFinal/src/ArjunWeekOneFinal.ino"
#define GREEN D6
#define YELLOW D5
#define BLUE D4
#define BUTTON1 D7
#define BUTTON2 D8
#define DIAL A5
#define TEMPSENSOR A4
#define TEMPSENSOR1 V6
#define TEMPSENSOR2 V7
#define NOTIFY_EVENT_CODE "notify"
#define HIGHMSG "Light Level Too High!"
#define LOWMSG "Light Level Too Low!"

SYSTEM_MODE(MANUAL); // remember to remove
SYSTEM_THREAD(ENABLED);

OledWingAdafruit display;
VCNL4040 proximitySensor;

int lightValue;
int proxValue;
int dialValue;
int reading;

int Button1 = LOW;

int setHigh;
int setLow;

bool lvt;
bool lvr = false;

void setup()
{
    display.setup();
    Serial.begin(9600);
    Wire.begin();
    Blynk.begin(BLYNK_AUTH_TOKEN);

    proximitySensor.begin();
    proximitySensor.powerOnAmbient();
    proximitySensor.enableWhiteChannel();

    pinMode(GREEN, OUTPUT);
    pinMode(YELLOW, OUTPUT);
    pinMode(BLUE, OUTPUT);

    pinMode(TEMPSENSOR, INPUT);
}

void loop()
{
    Blynk.run();
    display.loop();
    proxValue = proximitySensor.getProximity();
    lightValue = proximitySensor.getAmbient();
    dialValue = analogRead(DIAL);
    reading = analogRead(TEMPSENSOR);
    double voltage = (reading * 3.3) / 4095.0;
    double temperature = (voltage - 0.5) * 100;
    double ftemp = (temperature * 1.8) + 32;

    Blynk.virtualWrite(TEMPSENSOR1, temperature);
    Blynk.virtualWrite(TEMPSENSOR2, ftemp);

    display.clearDisplay();
    display.display();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.display();

    Serial.print(dialValue);
    Serial.println("");

    Button1 = digitalRead(BUTTON1);

    if (display.pressedA(){
        lvt = true;
    }
    if (display.pressedB(){
        lvt = false;
    }
    if (lvt){
        display.println("Light Mode");
        display.diplay();
        if (Button1 == HIGH)
        {
            lvr = true;
        }
        if (display.pressedB())
        {
            lvr = false;
        }

        if (lvr)
        {
            LowValue();
            setLow = dialValue;
        }
        else
        {
            HighValue();
            setHigh = dialValue;
        }
    }
        else
        {
        display.printf("%f C \n", temperature);
        display.println(" ");
        display.printf("%f F \n", ftemp);
        display.println(" ");
        display.display();
        }

        if (lightValue < setLow)
        {
        digitalWrite(GREEN, LOW);
        digitalWrite(YELLOW, LOW);
        digitalWrite(BLUE, HIGH);
        Blynk.logEvent(NOTIFY_EVENT_CODE, LOWMSG);
        }
        if (lightValue > setLow && lightValue < setHigh)
        {
        digitalWrite(GREEN, LOW);
        digitalWrite(YELLOW, HIGH);
        digitalWrite(BLUE, LOW);
        }
        if (lightValue > setHigh)
        {
        digitalWrite(GREEN, HIGH);
        digitalWrite(YELLOW, LOW);
        digitalWrite(BLUE, LOW);
        Blynk.logEvent(NOTIFY_EVENT_CODE, HIGHMSG);
        }
}

void ResetDisplay()
{
    display.clearDisplay();
    display.setCursor(0, 0);
}

void LowValue()
{
    ResetDisplay();
    display.println("Low Value");
    display.println("");
    display.println(dialValue);
    display.display();
}

void HighValue()
{
    ResetDisplay();
    display.println("High Value");
    display.println("");
    display.print(dialValue);
    display.display();
}