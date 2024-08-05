#include "wifi_conn.h"

Wifi_connector::Wifi_connector(String ssid, String password) {
    this->ssid = ssid;
    this->password = password;
}

void Wifi_connector::check() {
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
}

void Wifi_connector::connect() {
    WiFi.begin(this->ssid, this->password);
    Serial.print("Connecting");
    Wifi_connector::check();
    Serial.println();
    Serial.println("WiFi connection established.");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}
