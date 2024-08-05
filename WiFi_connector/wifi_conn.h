#ifndef WIFI_CONN_H
#define WIFI_CONN_H

#include <ESP8266WiFi.h>

class Wifi_connector {
    private:
        String ssid;
        String password;

    public:
        Wifi_connector(String ssid, String password);
        void check();
        void connect();
};

#endif
