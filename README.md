# OTA Upload Tool for Firmware and SPIFFS File System
This tool is designed for the [EUC Speedo project](https://github.com/ihatechoosingusernames/EUCSpeedo) but can be used with any ESP32 with an OTA (Over the Air) partition scheme.

It allows the upload of firmware.bin and spiffs.bin compiled binaries via the ESP32's builtin WiFi Access Point.

# How to Use:
- Upload this tool's compiled binary to the ESP32 either over the air or manually.
- Use a device with a web browser to search for a WiFi network named `Firmware-Upload`.
- Connect to this network, and in your browser type `192.168.4.1/` into the address bar.
- Press the `Upload` button, and select both the spiffs.bin and firmware.bin files you wish to upload.
- A popup will appear telling you to wait, this means the upload has begun.
- After 1 - 2 minutes, another popup will appear, either to announce a successful upload or an error.
- The device will restart and begin running the new firmware.

# Troubleshooting
- Ensure the compiled binaries uploaded are compiled for the specific device you are using.
- Ensure the device has a partition scheme that has sectors for both SPIFFS and OTA.