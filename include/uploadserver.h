#ifndef UPLOADSERVER_H_
#define UPLOADSERVER_H_

#include "ESPAsyncWebServer.h"
#include "AsyncTCP.h"

namespace upload_server {

class UploadServer {
  public:
    UploadServer();
  
  private:
    void ProcessMainPage(AsyncWebServerRequest *request);
    void ProcessUpdateUpload(AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final);
    void ProcessUpdateRequest(AsyncWebServerRequest *request);

    AsyncWebServer server;
    bool final_upload = false;
};

}

#endif