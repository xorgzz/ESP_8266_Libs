#include "web_server.h"

ESP8266WebServer server(80);

Web_server::Web_server() {
    server.on("/",          HTTP_GET,  [this]() { handle_root(); });
    server.on("/style.css", HTTP_GET,  [this]() { handle_css(); });
    server.on("/update",    HTTP_POST, [this]() { handle_post(); });
    server.onNotFound([this]() { handle_404(); });
    server.begin();
    while (true) {
        server.handleClient();
    }
}


void Web_server::handle_root() {
    Serial.printf("200: %s %s\n", server.uri(), (server.method() == HTTP_GET) ? "GET" : "POST");
    server.send(200, "text/html", "" /* <- here put your html code for main page */);
}

void Web_server::handle_css() {
    Serial.printf("200: %s %s\n", server.uri(), (server.method() == HTTP_GET) ? "GET" : "POST");
    server.send(200, "text/css", "" /* <- here put your css code */);
}

void Web_server::handle_post() {
	/*
		here do what you want
		
		server.hasArg("argument"); - gives you bool whether argument exists
		server.arg("argument");    - gives you the value of the argument
		
	*/
	
	// retrun viewer to root page
    server.send(200, "text/html", "<meta http-equiv=\"refresh\" content=\"0; url=/\" />");
}

void Web_server::handle_404() {
    Serial.printf("404: %s %s\n", server.uri(), (server.method() == HTTP_GET) ? "GET" : "POST");
    server.send(404, "text/html", "<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><title>404</title><link rel=\"stylesheet\" href=\"./style.css\"></head><body>404</body></html>");
}
