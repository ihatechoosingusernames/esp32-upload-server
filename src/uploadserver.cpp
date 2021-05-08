#include "uploadserver.h"

#include <functional>
#include <Update.h>

#include "mainpage.h"

namespace upload_server {

UploadServer::UploadServer() : server(80) {
  server.onNotFound([](AsyncWebServerRequest *request){ request->send(404); }); // Deal with all undefined requests

  server.on("/", HTTP_GET, std::bind(&UploadServer::ProcessMainPage, this, std::placeholders::_1));

  server.on("/update", HTTP_POST, std::bind(&UploadServer::ProcessUpdateRequest, this, std::placeholders::_1),
      std::bind(&UploadServer::ProcessUpdateUpload, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6));

  // Turning on WiFi AP
  WiFi.mode(WIFI_MODE_AP);
  WiFi.softAP("EUC-Speedo");
  server.begin();
}

void UploadServer::ProcessMainPage(AsyncWebServerRequest* request) {
  request->send(200, "text/html", kMainPage);
}

void UploadServer::ProcessUpdateRequest(AsyncWebServerRequest *request) {
  AsyncWebServerResponse *response = request->beginResponse(200, "text/plain", (Update.hasError() ? "FAIL" : "OK"));
  response->addHeader("Connection", "close");
  request->send(response);
}

void UploadServer::ProcessUpdateUpload(AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final) {
  if(!index && filename.equals("firmware.bin")) {
    if(!Update.begin((ESP.getFreeSketchSpace() - 0x1000) & 0xFFFFF000)){
      request->send(400);
    }
  } else if (!index && filename.equals("spiffs.bin")) {
    if(!Update.begin(UPDATE_SIZE_UNKNOWN, U_SPIFFS)) {
      request->send(400);
    }
  }
  if (!Update.hasError()) {
    if(Update.write(data, len) != len){
      request->send(400);
    }
  }
  if(final){
    if(Update.end(true)){
      if (final_upload) {
        request->send(200);
        ESP.restart();
      } else {
        final_upload = true;
      }
    } else {
      request->send(400);
    }
  }
}

}