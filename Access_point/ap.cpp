#include "ap.h"

Access_point::Access_point() {
    WiFi.mode(WIFI_AP);
    WiFi.softAP("" /* <- here put ssid */, "" /* <- here put password */);
    WiFi.softAPConfig(IPAddress(10, 0, 0, 1), IPAddress(10, 0, 0, 1), IPAddress(255, 255, 255, 0)); // set ip and netmask to whatever you want
}
