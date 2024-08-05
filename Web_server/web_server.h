#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include <ESP8266WebServer.h>

class Web_server {
    public:
        Web_server();
        void handle_root();
        void handle_css();
        void handle_post();
        void handle_404();
};

#endif
