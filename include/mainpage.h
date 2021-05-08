#ifndef MAINPAGE_H_
#define MAINPAGE_H_

#include <Arduino.h>

namespace upload_server {

// I hate this
static const String kMainPage = "<!DOCTYPE html>"
"<html>\n"
"<head>\n"
"  <title>UI Settings</title>\n"
"  <meta charset=\"utf-8\" />\n"
"</head>\n"
"<body>\n"
" <input type=\"file\" id=\"firmware\" style=\"display:none;\" onchange=\"uploadFirmware()\" multiple><button\n"
"   type=\"button\" style=\"float: left\" onclick=\"document.getElementById('firmware').click();\">Upload</button>\n"
" <script>\n"
" function uploadFirmware() {\n"
"   files = document.getElementById(\"firmware\").files;\n"
"\n"
"   if (files.length < 2) {\n"
"     alert(\"Both firmware.bin and spiffs.bin must be uploaded\");\n"
"     return;\n"
"   }\n"
"\n"
"   has_spiffs = files[0].name == \"spiffs.bin\" || files[1].name == \"spiffs.bin\";\n"
"   has_firmware = files[0].name == \"firmware.bin\" || files[1].name == \"firmware.bin\";\n"
"\n"
"   if (!(has_spiffs && has_firmware)) {\n"
"     alert(\"Chosen files do not include spiffs.bin and firmware.bin\");\n"
"     return;\n"
"   }\n"
"\n"
"   req = new XMLHttpRequest();\n"
"   formData = new FormData();\n"
"\n"
"   req.onload = function () {\n"
"     if (req.status == 200) {\n"
"       alert(\"Update uploaded successfully, device will now restart\");\n"
"     } else {\n"
"       alert(\"There's been a problem with the upload, ensure those were the correct files.\");\n"
"     }\n"
"   }\n"
"\n"
"   formData.append(files[0].name, files[0]);\n"
"   if (files.length == 2) {\n"
"     formData.append(files[1].name, files[1]);\n"
"   }\n"
"   req.open(\"POST\", \"update\");\n"
"   req.send(formData);\n"
"   alert(\"Uploading, please wait...\");\n"
"  }\n"
" </script>\n"
"</body>\n"
"</html>";

}

#endif