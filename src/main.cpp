#include <Arduino.h>

#include "uploadserver.h"

using namespace upload_server;

UploadServer* server;

void setup() {
  server = new UploadServer();
}

void loop() {}  // Nothing happens here, the server handles it