/*
 * ota_updater
 * 
 * Description: Demo using OTA (Over The Air) updates on ESP32 from any webserver
 *              The "ota_control" tab can be copied to other projects, to permit
 *              OTA updates from any http/s server hosting appropriate files. See
 *              comments in ota_control for call descriptions.
 * 
 * NB: We can only make use of the otc_control class in Arduino IDE tabs that appear AFTER
 *     the class is declared which is why we have zz_util
 *
 * NB: This file is just the test harness for ota_control
 */

#include <WiFi.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin (115200);  // start a console
  
  // OTA presupposes WiFi is working
  Serial.println ("Wait for WiFi");
  WiFi.begin("YOUR_SSID", "YOUR_SSID_PASSWORD");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print (".");
    delay (1000);
  }
  Serial.println (".");
  // We need to set the clock if using HTTPS to verify certificate
  setClock();  

  // Try to do OTA update twice, only the fist will succeed in updating the unit
  Serial.println ("10 second delay before starting check...");
  delay (10000);
  Serial.println ("OTA update starting.");
  check4update();
  Serial.println ("Demo complete.");
}

void loop() {
  // put your main code here, to run repeatedly:
  sleep (3600);
}

/*
 * Need time to check for https certificate expiry
 * We don't need to adjust to local time zone, UTC is sufficient
 * Tis is only needed for HTTPS, HTTP will work without adjusting time.
 */
void setClock() {
  configTime(0, 0, "pool.ntp.org", "time.nist.gov");

  Serial.print(F("Waiting for NTP time sync: "));
  time_t nowSecs = time(nullptr);
  while (nowSecs < 8 * 3600 * 2) {
    delay(500);
    Serial.print(F("."));
    yield();
    nowSecs = time(nullptr);
  }
  // Print the time, NB: this will be UTC.
  Serial.println();
  struct tm timeinfo;
  gmtime_r(&nowSecs, &timeinfo);
  Serial.print(F("Current time: "));
  Serial.print(asctime(&timeinfo));
}
