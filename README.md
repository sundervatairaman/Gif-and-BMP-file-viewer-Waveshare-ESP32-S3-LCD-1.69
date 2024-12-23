# WaveShare ESP32 S3 LCD 1.69 TFT GIF Display Project

This project demonstrates displaying GIFs, BMPs, 
on an ST7789 TFT screen using an ESP32 S3 LCD 1.69 and ESP32 C6 LCD 1.47. It also supports  FFat for file handling. Python code to convert .gif to .h file

## Features
- Display GIF animations, BMP images.
- File storage using FFat.
- TFT screen brightness control with PWM.
- File listing and partition information display.

<img src="IMG_17172.gif" width="400" />


## Hardware Requirements
- ESP32 S3 LCD 1.69  board
- ESP32 C6 LCD 1.47
- ST7789 TFT display

<img src="ffts.gif" width="800" />


## Software Requirements
- Arduino IDE with the following libraries:
  - [Adafruit GFX Library](https://github.com/adafruit/Adafruit-GFX-Library)
  - [Adafruit ST7789 Library](https://github.com/adafruit/Adafruit-ST7735-Library)
  - [JPEGDecoder](https://github.com/Bodmer/JPEGDecoder)
  - LittleFS and FFat support for ESP32

## Wiring Diagram ESP32 S3 LCD 1.67
| ESP32 Pin | TFT Pin        |
|-----------|----------------|
| GPIO 5    | CS             |
| GPIO 4    | DC             |
| GPIO 6    | SCLK           |
| GPIO 7    | MOSI           |
| GPIO 8    | RESET          |
| GPIO 15   | Backlight (PWM)|

## Getting Started
1. Clone this repository:
   ```bash
   git clone https://github.com/<your-username>/esp32_tft_gif_display.git
