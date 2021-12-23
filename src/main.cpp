// ==========================================================================================
// Jeeves.BoilerPlate
// main.cpp
//
// MIT License
//
// Copyright (c) 2020-2021 Paolo Marcucci
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
// ==========================================================================================

#define SENSOR_TYPE "ModulAmp"  // type of sensor
#define VERSION     "1.0"       // firmware version
#define MAIN_TOPIC  "modulamp"  // default MQTT topic (can be empty)

#include "main.h"
#include "EEPROM.h"

// Global variables -------------------------------------------------------------------------

// - Fonts
#define HEADER_FONT u8g2_font_logisoso16_tf
#define BODY_FONT u8g2_font_logisoso34_tf

// - Smart knob values
#define KNOB_MODE_MENU 0
#define KNOB_MODE_VOLUME 1
#define KNOB_MODE_INPUT 2

int KNOB_MODE_MENU_MAX = 2;
int KNOB_MODE_MENU_MIN = 1;

#define KNOB_INPUT_STREAM 0
#define KNOB_INPUT_LINE1 1
#define KNOB_INPUT_LINE2 2
#define KNOB_INPUT_BACK 3

int KNOB_MODE_INPUT_MAX = 2;
int KNOB_MODE_INPUT_MIN = 0;

int KNOB_MODE_VOLUME_MAX = 20;
int KNOB_MODE_VOLUME_MIN = 0;

int KNOB_MODE = KNOB_MODE_VOLUME;

int KNOB_MENU = KNOB_MODE_VOLUME;
int KNOB_INPUT = KNOB_INPUT_STREAM;
int KNOB_SELECTED_INPUT = KNOB_INPUT;
int KNOB_VOLUME = KNOB_MODE_VOLUME_MIN;

boolean KNOB_BUTTON_PRESSED = false;

#define DELTA 1

// - DHTxx values
float DHT_TEMPERATURE;
float DHT_HUMIDITY;

// TODO: add global variables here
int addr = 0;

// MQTT sensor specific topics to report values ---------------------------------------------
char input_mqtt_topic[50];
char volume_mqtt_topic[50];

// ==========================================================================================
// IMPLEMENTATION
// ==========================================================================================

// ==========================================================================================
// HW routines
// ==========================================================================================

void selectInput(int value)
{
  KNOB_INPUT = value;
}

void setVolume(int value)
{
  KNOB_VOLUME = value;
}

void saveVolume(int value)
{
  /* code */
  // EEPROM.put(0, (uint8_t)KNOB_VOLUME);
  //   EEPROM.commit();
  // Serial.print("Saving volume ");
  // Serial.println(KNOB_VOLUME);
}

void saveInput(int value)
{
  /* code */
  // EEPROM.put(1, (uint8_t)KNOB_INPUT);
  //   EEPROM.commit();
  // Serial.print("Saving input ");
  // Serial.println(KNOB_INPUT);
}

int getVolume()
{
  uint8_t v = 0;

  // v = EEPROM.read(0);
  // Serial.print("Reading volume ");
  // Serial.println(v);
  return ((int)v);
}

int getInput()
{
  uint8_t v = 0;

  // v = EEPROM.read(1);
  // Serial.print("Reading input ");
  // Serial.println(v);
  return ((int)v);
}

void resetScreenTimeout()
{
  screenTimeoutTimer = millis();
  SCREEN_ACTIVE = true;
}

// ------------------------------------------------------------------------------------------
// Step 1/7 - Add any sensor-specific initialization code
// ------------------------------------------------------------------------------------------

void sensorSetup()
{
  char s[80];
  IPAddress ip = WiFi.localIP();

  if (SENSOR_SSD1306) // - SSD1306 I2C OLED DISPLAY
  {
    u8g2.begin();

    // Show splash screen
    // TODO redesign the splash screen
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_helvB12_tr);
    sprintf(s, "%s", SENSOR_TYPE);
    u8g2.drawStr(0, 18, s);
    u8g2.setFont(u8g2_font_profont12_mf);
    sprintf(s, "ID :%06X", DEVICE_ID);
    u8g2.drawStr(0, 32, s);
    sprintf(s, "IP :%u.%u.%u.%u", ip[0], ip[1], ip[2], ip[3]);
    u8g2.drawStr(0, 42, s);
    sprintf(s, "Loc:%s", LOCATION);
    u8g2.drawStr(0, 52, s);
    sprintf(s, "Ver:%s", VERSION);
    u8g2.drawStr(0, 62, s);
    u8g2.sendBuffer();
    // End splash screen

    ON_SPLASH_SCREEN = true;
  }

  if (SENSOR_DHT) // - DHTxx TEMPERATURE AND HUMIDITY SENSOR
  {
    dht.begin();
  }

  if (SENSOR_HD74480) // - HD77480 16x2 LCD DISPLAY
  {
    char client_id[20];

    lcd.init();

    // Show splash screen
    lcd.backlight();
    lcd.setCursor(0, 0);
    sprintf(client_id, "Jeeves    %x", DEVICE_ID);
    lcd.print(client_id);
    lcd.setCursor(0, 1);
    lcd.print(SENSOR_TYPE);
    lcd.setCursor(13, 1);
    lcd.print(VERSION);
    // End splash screen

    ON_SPLASH_SCREEN = true;
  }

  if (SENSOR_KY040) // - KY040 ROTARY ENCODER
  {
    pinMode(KY040_PIN_IN1, INPUT);
    pinMode(KY040_PIN_IN1, INPUT_PULLUP);
    pinMode(KY040_PIN_IN2, INPUT);
    pinMode(KY040_PIN_IN2, INPUT_PULLUP);
    pinMode(KY040_PIN_BUTTON, INPUT);
    pinMode(KY040_PIN_BUTTON, INPUT_PULLUP);

    KNOB_MODE = KNOB_MODE_VOLUME;
    KNOB_VOLUME = getVolume();
    KNOB_INPUT = getInput();
  }

  // TODO: Add other sensor-specific initialization code here
  /* code */
  EEPROM.begin(512);
}

// ------------------------------------------------------------------------------------------
// Step 2/7 - Setup the MQTT topics
// ------------------------------------------------------------------------------------------
void sensorMqttSetup()
{
  sprintf(input_mqtt_topic, "%s/%s", LOCATION, "audioinput");
  sprintf(volume_mqtt_topic, "%s/%s", LOCATION, "volume");
}

// ------------------------------------------------------------------------------------------
// Step 3a/7 - Read data from the sensor(s) timed every DELAY_MS milliseconds
// ------------------------------------------------------------------------------------------
void sensorUpdateReadings()
{
  // Saving status to EEPROM
  saveVolume(KNOB_VOLUME);
  saveInput(KNOB_INPUT);
}

// ------------------------------------------------------------------------------------------
// Step 3b/7 - Read data from the sensor(s) on every loop
// ------------------------------------------------------------------------------------------
void sensorUpdateReadingsQuick()
{
  if (SENSOR_KY040) // - KY040 rotary encoder readings
  {
    switch (KY040_STATUS_CURRENT)
    {
    case KY040_STATUS_PRESSED:
      // flip between states
      switch (KNOB_MODE)
      {
      case KNOB_MODE_MENU: // select the current menu entry
        KNOB_MODE = KNOB_MENU;
        break;
      case KNOB_MODE_INPUT: // select the input
        KNOB_SELECTED_INPUT = KNOB_INPUT;
        selectInput(KNOB_SELECTED_INPUT);
        KNOB_MODE = KNOB_MODE_VOLUME; // go directly to volume
        break;
      case KNOB_MODE_VOLUME: // go back to the menu
        KNOB_MODE = KNOB_MODE_MENU;
        break;
      default:
        break;
      }

      ON_SPLASH_SCREEN = false;
      resetScreenTimeout();
      sensorUpdateDisplay();
      KY040_STATUS_CURRENT = KY040_STATUS_IDLE;
      break;

    case KY040_STATUS_GOINGUP:
      switch (KNOB_MODE)
      {
      case KNOB_MODE_MENU: // move to the next menu entry
        if (++KNOB_MENU > KNOB_MODE_MENU_MAX)
          KNOB_MENU = KNOB_MODE_MENU_MIN;
        break;
      case KNOB_MODE_INPUT: // move to the next input
        if (++KNOB_INPUT > KNOB_MODE_INPUT_MAX)
          KNOB_INPUT = KNOB_MODE_INPUT_MIN;
        break;
      case KNOB_MODE_VOLUME: // increment the volume
        if (KNOB_VOLUME < KNOB_MODE_VOLUME_MAX)
          KNOB_VOLUME += DELTA;
        setVolume(KNOB_VOLUME);
        break;
      default:
        break;
      }

      ON_SPLASH_SCREEN = false;
      Serial.println(KNOB_VOLUME);
      resetScreenTimeout();
      sensorUpdateDisplay();
      KY040_STATUS_CURRENT = KY040_STATUS_IDLE;
      break;

    case KY040_STATUS_GOINGDOWN:
      switch (KNOB_MODE)
      {
      case KNOB_MODE_MENU: // move to the prev menu entry
        if (--KNOB_MENU < KNOB_MODE_MENU_MIN)
          KNOB_MENU = KNOB_MODE_MENU_MAX;
        break;
      case KNOB_MODE_INPUT: // move to the prev input
        if (--KNOB_INPUT < KNOB_MODE_INPUT_MIN)
          KNOB_INPUT = KNOB_MODE_INPUT_MAX;
        break;
      case KNOB_MODE_VOLUME: // decrement the volume
        if (KNOB_VOLUME > KNOB_MODE_VOLUME_MIN)
          KNOB_VOLUME -= DELTA;
        setVolume(KNOB_VOLUME);
        break;
      default:
        break;
      }

      ON_SPLASH_SCREEN = false;
      Serial.println(KNOB_VOLUME);
      resetScreenTimeout();
      sensorUpdateDisplay();
      KY040_STATUS_CURRENT = KY040_STATUS_IDLE;
      break;

    default:
      break;
    }
  }

  // TODO: Perform measurements on every loop
  /* code */
}

// ------------------------------------------------------------------------------------------
// Step 4/7 - Send the values to the MQTT server
// ------------------------------------------------------------------------------------------
void sensorReportToMqtt()
{
  bool emitTimestamp = false;

  sendToMqttTopicAndValue(input_mqtt_topic, String(KNOB_SELECTED_INPUT));
  sendToMqttTopicAndValue(volume_mqtt_topic, String(KNOB_VOLUME));

  if (emitTimestamp) // Common timestamp for all MQTT topics pub
  {
    time_t temp;
    struct tm *timeptr;
    char s[80], t[80];

    temp = time(NULL);
    timeptr = localtime(&temp);

    strftime(s, sizeof(s), "%Y-%m-%d %T", timeptr);
    sprintf(t, "%s/%s", LOCATION, STR_SENSOR_TOPIC_TIMESTAMP);
    sendToMqttTopicAndValue(t, s);
  }
}

// ------------------------------------------------------------------------------------------
// Step 5/7 - Report the latest values to the serial console
// ------------------------------------------------------------------------------------------
void sensorReportToSerial()
{
  // TODO: report required values to the console
  /* code */
}

// ------------------------------------------------------------------------------------------
// Step 6/7 - Update the local display
// ------------------------------------------------------------------------------------------
void sensorUpdateDisplay()
{
  if (SCREEN_ACTIVE) // update the display only if active
  {
    if (!ON_SPLASH_SCREEN) // update the display only if the splash screen has been dismissed
    {
      if (SENSOR_SSD1306)
      {
        char s[20];
        u8g2.clearBuffer();
        switch (KNOB_MODE)
        {
        // TODO redesign the screens for menu, input, volume
        case KNOB_MODE_MENU:
          u8g2.setFont(HEADER_FONT);
          sprintf(s, "%s", "MODULAMP");
          u8g2.drawStr(0, 16, s);

          u8g2.setFont(BODY_FONT);
          switch (KNOB_MENU)
          {
          case KNOB_MODE_INPUT:
            sprintf(s, "%s", "INPUT");
            break;
          case KNOB_MODE_VOLUME:
            sprintf(s, "%s", "VOLUME");
            break;
          }
          u8g2.drawStr(0, 60, s);
          break;

        case KNOB_MODE_INPUT:
          u8g2.setFont(HEADER_FONT);
          sprintf(s, "%s", "INPUT");
          u8g2.drawStr(0, 16, s);

          u8g2.setFont(BODY_FONT);
          switch (KNOB_INPUT)
          {
          case KNOB_INPUT_BACK:
            sprintf(s, "%s", "MENU");
            break;
          case KNOB_INPUT_STREAM:
            sprintf(s, "%s", "STREAM");
            break;
          case KNOB_INPUT_LINE1:
            sprintf(s, "%s", "PHONO");
            break;
          case KNOB_INPUT_LINE2:
            sprintf(s, "%s", "AUX");
            break;
          }
          u8g2.drawStr(0, 60, s);
          break;

        case KNOB_MODE_VOLUME:
          u8g2.setFont(HEADER_FONT);
          sprintf(s, "%s", "VOLUME");
          u8g2.drawStr(0, 16, s);

          u8g2.setFont(BODY_FONT);
          sprintf(s, "%d", KNOB_VOLUME);
          u8g2.drawStr(0, 60, s);
          break;

        default:
          break;
        }

        u8g2.sendBuffer();
      }

      /* code */ // <-- other indicators and annunciators
    }
  }
  else
  {
    u8g2.clearBuffer();
    u8g2.sendBuffer();
  }
}

// ------------------------------------------------------------------------------------------
// Step 7/7 (optional) - This callback is invoked when an MQTT message is received.
// ------------------------------------------------------------------------------------------
void mqttCallback(char *topic, byte *payload, uint8_t length)
{
  // Prepare message
  String message = "";
  for (int i = 0; i < int(length); i++)
  {
    message += (char)payload[i];
  }

  // log message
  char out[255];
  sprintf(out, STR_MESSAGE_RECEIVED_FORMAT, topic, message.c_str());
  log_out("MQTT", out);

  // TODO: error handling
  int v;
  sscanf(message.c_str(), "%s %d", c, &v);

      char s[255];
      sprintf(s,"Parameter:%s - Value:%d", c, v);
      Serial.println(s);

  if (!strcmp(c, "volume")) setVolume(v);
  if (!strcmp(c, "input")) selectInput(v);

}
