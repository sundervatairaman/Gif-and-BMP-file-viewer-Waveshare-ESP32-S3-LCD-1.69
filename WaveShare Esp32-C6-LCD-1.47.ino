#define FS_NO_GLOBALS
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h> // Replace with your display library
#include <FS.h>
#include <SPIFFS.h>
#define CUSTOM_PARTITIONS_H
#include <FS.h>
#include <LittleFS.h> // Include LittleFS header
#include <JPEGDecoder.h> // Install JPEGDecoder library
#include "esp_partition.h"
#include <stdio.h>
#include <string.h>
#include "esp_vfs.h"
#include "esp_vfs_fat.h"
#include "esp_spiffs.h"
#include "FFat.h"
//#include <M5Stack.h>
#include <EEPROM.h>
#define VSPI 1
#include <SPI.h>
SPIClass spi = SPIClass(VSPI);
#include <driver/gpio.h>
#include <SD.h>
#include <AnimatedGIF.h>
#include "BmpClass.h"
static BmpClass bmpClass;
#include "GifClass.h"
static GifClass gifClass;
#include "../test_images/pingu1.h"
#include "../test_images/yoda1.h"
#include "../test_images/minion2.h"


#define TFT_CS         14
#define TFT_RST        21 // Or set to -1 and connect to Arduino RESET pin
#define TFT_DC         15
#define TFT_MOSI       6  // Data out
#define TFT_MISO       5  // Not used
#define TFT_SCLK       7  // Clock out
#define TFT_BL         22

#define DISPLAY_WIDTH 172
#define DISPLAY_HEIGHT 320

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);
AnimatedGIF gif;
File f;

void setup() {
  Serial.begin(115200);
  Serial.print(F("Hello! ST77xx TFT Test"));
  pinMode(15, OUTPUT);
  digitalWrite(15, HIGH); // sets the digital pin 13 on
  #define freq 1000
  #define resolution 8
  #define dutyCycle 16 // Use 0-255 to vary brightness
  ledcAttach(TFT_BL, freq, resolution);
  ledcWrite(TFT_BL, dutyCycle);
  SPI.begin(TFT_SCLK, TFT_MISO, TFT_MOSI, TFT_CS);
  tft.init(240, 280);
  tft.fillScreen(ST77XX_BLACK); // Fill with blue to check visibility
  // large block of text
  // Mount LittleFS
  const esp_partition_t *partition = esp_partition_find_first(ESP_PARTITION_TYPE_DATA, ESP_PARTITION_SUBTYPE_DATA_FAT, "ffat");
  if (partition != NULL) {
    tft.println("FFat Partition Info:\n");
    tft.printf("  Start Address: 0x%08x\n", partition->address);
    tft.printf("  Size: 0x%08x (%d bytes)\n", partition->size, partition->size);
  } else {
    tft.println("FFat partition not found!\n");
  }

  esp_partition_iterator_t iter = esp_partition_find(ESP_PARTITION_TYPE_APP, ESP_PARTITION_SUBTYPE_APP_FACTORY, NULL);
  while (iter != NULL) {
    const esp_partition_t *partition = esp_partition_get(iter);
    tft.printf("Partition Label: %s\n", partition->label);
    tft.printf("Partition Offset: 0x%x\n", partition->address);
    tft.printf("Partition Size: 0x%x\n", partition->size);
        
    iter = esp_partition_next(iter);
  }

  // Mount SPIFFS
  //if (!SPIFFS.begin(true)) {
    //Serial.println("SPIFFS Mount Failed");
    //tft.println("SPIFFS Mount Failed");
    //return;
  //}
  //tft.println("SPIFFS Mounted");

  FFat.begin(true);
     
  //writeFFatFile(FFat, "/hello.txt", "Hello ");
  //writeFFatFile(FFat, "/second.txt", "second\n");
  //readFFatFile(FFat, "/second.txt");

  //File file = SPIFFS.open("/hello.txt", FILE_WRITE);
  //if (!file) {
    //tft.println("Failed to open file for writing");
    //return;
  //}

  //file.println("Hello, SPIFFS!");
  //file.close();
  //tft.println("File written successfully");
  //file.close();
  
  //const char *file_path = "/s1.jpg";

  // Check if file exists
  //if (!SPIFFS.exists(file_path)) {
    //tft.println("File does not exist.");
    //return;
  //}

  //// Open file for reading
  //File readFile = SPIFFS.open(file_path, FILE_READ);
  //if (!readFile) {
    //tft.println("Failed to open file for reading");
    //return;
  //}

  // Read file content
  //tft.println("File Content:");
  //while (readFile.available()) {
    //tft.write(readFile.read()); // Output the file content to Serial Monitor
  //}

  //readFile.close();
  //tft.println("\nFile read successfully.");
  

}

void loop() {
  tft.setRotation(2);  // portrait
  pinMode(TFT_BL, OUTPUT);  // Set the pin as output
  analogWrite(TFT_BL, 255);  // Set brightness to maximum (0 to 255 range)
  tft.fillScreen(ST77XX_BLACK);
  listFFat();
  delay(2000);
  tft.fillScreen(ST77XX_BLACK);
  
  gif.begin(LITTLE_ENDIAN_PIXELS);
  





  
  
  // put your main code here, to run repeatedly:
  if (gif.open((uint8_t *)pingu1, sizeof(pingu1), GIFDraw))
  {
    Serial.printf("Successfully opened GIF; Canvas size = %d x %d\n", gif.getCanvasWidth(), gif.getCanvasHeight());
    unsigned long startTime = millis(); // Record the start time
    while (millis() - startTime < 8000) { // Run for 8000 milliseconds
      if (!gif.playFrame(true, NULL)) { 
        // Restart GIF if it finishes within the 8000ms
        //gif.restart();
      }
    }
    gif.close();
  }


  delay(8000);


  // put your main code here, to run repeatedly:
  if (gif.open((uint8_t *)yoda1, sizeof(yoda1), GIFDraw))
  {
    Serial.printf("Successfully opened GIF; Canvas size = %d x %d\n", gif.getCanvasWidth(), gif.getCanvasHeight());
    unsigned long startTime = millis(); // Record the start time
    while (millis() - startTime < 8000) { // Run for 8000 milliseconds
      if (!gif.playFrame(true, NULL)) { 
        // Restart GIF if it finishes within the 8000ms
        //gif.restart();
      }
    }
    gif.close();
  }


  delay(8000);

// put your main code here, to run repeatedly:
  if (gif.open((uint8_t *)minion2, sizeof(minion2), GIFDraw))
  {
    Serial.printf("Successfully opened GIF; Canvas size = %d x %d\n", gif.getCanvasWidth(), gif.getCanvasHeight());
    unsigned long startTime = millis(); // Record the start time
    while (millis() - startTime < 8000) { // Run for 8000 milliseconds
      if (!gif.playFrame(true, NULL)) { 
        // Restart GIF if it finishes within the 8000ms
        //gif.restart();
      }
    }
    gif.close();
  }


  delay(8000);





  //listSPIFFS();
  // Draw the image
  if (!FFat.begin(true)) {
    tft.println("FFat Mount Failed");
    return;
  }
  //tft.setRotation(0);  // portrait
  //tft.fillScreen(random(0xFFFF));
  File bmpFile = FFat.open("/face280240.bmp", FILE_READ);
  //drawBmp("/octocatL.bmp", 0, 0);
  // read BMP file header
  bmpClass.draw(
    &bmpFile, bmpDrawCallback, false /* useBigEndian */,
    0 /* x */, 0 /* y */, tft.width() /* widthLimit */, tft.height() /* heightLimit */);

  bmpFile.close();
  delay(4000);
  File bmpFile1 = FFat.open("/dino1280240.bmp", FILE_READ);
  //drawBmp("/octocatL.bmp", 0, 0);
  // read BMP file header
  bmpClass.draw(
    &bmpFile1, bmpDrawCallback, false /* useBigEndian */,
    0 /* x */, 0 /* y */, tft.width() /* widthLimit */, tft.height() /* heightLimit */);

  bmpFile1.close();


  



}
//void loop() {}
// pixel drawing callback
static void bmpDrawCallback(int16_t x, int16_t y, uint16_t *bitmap, int16_t w, int16_t h)
{
  // Serial.printf("Draw pos = %d, %d. size = %d x %d\n", x, y, w, h);
  tft.drawRGBBitmap(x, y, bitmap, w, h);
}



void displayJPEG(const char *filename, int16_t x, int16_t y) {
    // Open the JPEG file
    File jpegFile = FFat.open(filename, "r");
    if (!jpegFile) {
        Serial.println("Failed to open JPEG file");
        return;
    }

    // Decode the JPEG file
    if (JpegDec.decodeFsFile(jpegFile) != 1) {
        Serial.println("Failed to decode JPEG");
        jpegFile.close();
        return;
    }

    // Verify the image fits on the display
    if (x + JpegDec.width > tft.width() || y + JpegDec.height > tft.height()) {
        Serial.println("Image too large for display");
        jpegFile.close();
        return;
    }

    // Render the JPEG image
    for (uint16_t row = 0; row < JpegDec.height; row++) {
        JpegDec.read(); // Decode a row of pixels
        uint16_t *rowPtr = JpegDec.pImage; // Get pointer to row data
        tft.drawRGBBitmap(x, y + row, rowPtr, JpegDec.width, 1);
    }

    Serial.println("JPEG displayed successfully");
    jpegFile.close();
}


void listSPIFFS() {
  tft.println("Listing SPIFFS files...");

  // Check if SPIFFS is mounted
  if (!SPIFFS.begin(true)) {
    tft.println("SPIFFS Mount Failed");
    return;
  }

  // Use SPIFFS to list files
  File root = SPIFFS.open("/");
  if (!root) {
    tft.println("Failed to open SPIFFS root directory");
    return;
  }

  if (!root.isDirectory()) {
    tft.println("Not a directory");
    return;
  }

  File file = root.openNextFile();
  while (file) {
    tft.printf("FILE: %s, SIZE: %d bytes\n", file.name(), file.size());
    file = root.openNextFile();
  }
}

void testdrawtext(char *text, uint16_t color) {
  tft.setCursor(0, 0);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}

void writeFFatFile(fs::FS &fs, const char *path, const char *message)
{
  tft.printf("Writing file: %s\r\n", path);
  File file = fs.open(path, FILE_WRITE);
  if (!file)
  {
    tft.println("- failed to open file for writing");
    return;
  }
  if (file.print(message))
  {
    tft.println("- file written");
  }
  else
  {
    tft.println("- write failed");
  }
}


void readFFatFile(fs::FS &fs, const char *path) {
  tft.printf("Reading file: %s\n", path);

  File file = fs.open(path);
  if (!file) {
    tft.println("Failed to open file for reading");
    return;
  }

  Serial.println("File Content:");
  while (file.available()) {
    Serial.write(file.read());
  }
  file.close();
}


void listFFat() {
  tft.println("Listing FFat files...");

  // Check if FFat is mounted
  if (!FFat.begin(true)) {
    tft.println("FFat Mount Failed");
    return;
  }

  // Use FFat to list files
  File root = FFat.open("/");
  if (!root) {
    tft.println("Failed to open FFat root directory");
    return;
  }

  if (!root.isDirectory()) {
    tft.println("Not a directory");
    return;
  }

  File file = root.openNextFile();
  while (file) {
    tft.printf("FILE: %s, SIZE: %d bytes\n", file.name(), file.size());
    file = root.openNextFile();
  }
}

// Function to draw a BMP file on the TFT
void drawBmp(const char *filename, int x, int y) {
    File bmpFile;
    uint8_t bmpHeader[54];
    int bmpWidth, bmpHeight, rowPadding;
    uint32_t imageOffset;

    // Open the BMP file
    bmpFile = FFat.open(filename, "r");
    if (!bmpFile) {
        tft.println("Failed to open BMP file");
        return;
    }

    // Read the BMP header
    if (bmpFile.read(bmpHeader, 54) != 54) {
        tft.println("Not a valid BMP file");
        bmpFile.close();
        return;
    }

    // Verify the BMP signature
    if (bmpHeader[0] != 'B' || bmpHeader[1] != 'M') {
        tft.println("Not a BMP file");
        bmpFile.close();
        return;
    }

    // Extract image dimensions and offset
    bmpWidth = *(int32_t *)&bmpHeader[18];
    bmpHeight = *(int32_t *)&bmpHeader[22];
    imageOffset = *(uint32_t *)&bmpHeader[10];

    // Ensure BMP fits within the display
    if (x + bmpWidth > tft.width() || y + bmpHeight > tft.height()) {
        tft.println("BMP image too large for display");
        bmpFile.close();
        return;
    }

    // Calculate row padding (each row's data is a multiple of 4 bytes)
    rowPadding = (4 - (bmpWidth * 3) % 4) % 4;

    // Start reading pixel data from the BMP
    bmpFile.seek(imageOffset);
    for (int row = 0; row < bmpHeight; row++) {
        for (int col = 0; col < bmpWidth; col++) {
            // Read RGB values (BMP is stored in BGR order)
            uint8_t b = bmpFile.read();
            uint8_t g = bmpFile.read();
            uint8_t r = bmpFile.read();

            // Convert to RGB565 and draw the pixel
            uint16_t color = tft.color565(r, g, b);
            tft.drawPixel(x + col, y + bmpHeight - 1 - row, color); // BMP rows are bottom-up
        }
        // Skip row padding bytes
        bmpFile.seek(bmpFile.position() + rowPadding);
    }

    bmpFile.close();
    tft.println("BMP displayed successfully");
}


// Draw a line of image directly on the LCD
void GIFDraw(GIFDRAW *pDraw)
{
    uint8_t *s;
    uint16_t *d, *usPalette, usTemp[320];
    int x, y, iWidth;

    iWidth = pDraw->iWidth;
    if (iWidth + pDraw->iX > DISPLAY_WIDTH)
       iWidth = DISPLAY_WIDTH - pDraw->iX;
    usPalette = pDraw->pPalette;
    y = pDraw->iY + pDraw->y; // current line
    if (y >= DISPLAY_HEIGHT || pDraw->iX >= DISPLAY_WIDTH || iWidth < 1)
       return; 
    s = pDraw->pPixels;
    if (pDraw->ucDisposalMethod == 2) // restore to background color
    {
      for (x=0; x<iWidth; x++)
      {
        if (s[x] == pDraw->ucTransparent)
           s[x] = pDraw->ucBackground;
      }
      pDraw->ucHasTransparency = 0;
    }

    // Apply the new pixels to the main image
    if (pDraw->ucHasTransparency) // if transparency used
    {
      uint8_t *pEnd, c, ucTransparent = pDraw->ucTransparent;
      int x, iCount;
      pEnd = s + iWidth;
      x = 0;
      iCount = 0; // count non-transparent pixels
      while(x < iWidth)
      {
        c = ucTransparent-1;
        d = usTemp;
        while (c != ucTransparent && s < pEnd)
        {
          c = *s++;
          if (c == ucTransparent) // done, stop
          {
            s--; // back up to treat it like transparent
          }
          else // opaque
          {
             *d++ = usPalette[c];
             iCount++;
          }
        } // while looking for opaque pixels
        if (iCount) // any opaque pixels?
        {
          tft.startWrite();
          tft.setAddrWindow(pDraw->iX+x, y, iCount, 1);
          tft.writePixels(usTemp, iCount, false, false);
          tft.endWrite();
          x += iCount;
          iCount = 0;
        }
        // no, look for a run of transparent pixels
        c = ucTransparent;
        while (c == ucTransparent && s < pEnd)
        {
          c = *s++;
          if (c == ucTransparent)
             iCount++;
          else
             s--; 
        }
        if (iCount)
        {
          x += iCount; // skip these
          iCount = 0;
        }
      }
    }
    else
    {
      s = pDraw->pPixels;
      // Translate the 8-bit pixels through the RGB565 palette (already byte reversed)
      for (x=0; x<iWidth; x++)
        usTemp[x] = usPalette[*s++];
      tft.startWrite();
      tft.setAddrWindow(pDraw->iX, y, iWidth, 1);
      tft.writePixels(usTemp, iWidth, false, false);
      tft.endWrite();
    }
} /* GIFDraw() */

