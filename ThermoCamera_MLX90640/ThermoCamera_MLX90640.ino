#include <Adafruit_MLX90640.h>
#include <Adafruit_GFX.h>     // Core graphics library
#include <Adafruit_ST7735.h>  // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h>  // Hardware-specific library for ST7789
#include <SPI.h>

// For the breakout board, you can use any 2 or 3 pins.
// These pins will also work for the 1.8" TFT shield.
#define TFT_CS 10
#define TFT_RST 9  // Or set to -1 and connect to Arduino RESET pin
#define TFT_DC 8
#define TFT_MOSI 11  // Data out
#define TFT_SCLK 13  // Clock out

// OPTION 1 (recommended) is to use the HARDWARE SPI pins, which are unique
// to each board and not reassignable. For Arduino Uno: MOSI = pin 11 and
// SCLK = pin 13. This is the fastest mode of operation and is required if
// using the breakout board's microSD card.
// For 1.14", 1.3", 1.54", 1.69", and 2.0" TFT with ST7789:
//Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);
// OR for the ST7789-based displays, we will use this call
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

Adafruit_MLX90640 mlx;
float frame[32 * 24];  // buffer for full frame of temperatures

//low range of the sensor (this will be blue on the screen)
#define MINTEMP 20

//high range of the sensor (this will be red on the screen)
#define MAXTEMP 35

// Width of the TFT in px
#define TFT_W 240

// Height of the TFT in px
#define TFT_H 240

// With of the MLX sensor on px
#define MLX_W 32

// Height of the MLX sensor in px
#define MLX_H 24

// MLX sensor is 32x24 pixels, but only the central area of 30x24
// will be read in order to be easy presented on the 240x240 TFT display

// First pixel in X direction to be read from the MLX sensor
#define MLX_READ_X_MIN 1

// Last pixel in X direction to be read from the MLX sensor
#define MLX_READ_X_MAX 31

// First pixel in Y direction to be read from the MLX sensor
#define MLX_READ_Y_MIN 0

// Last pixel in Y direction to be read from the MLX sensor
#define MLX_READ_Y_MAX 24

//the colors we will be using
const uint16_t camColors[] = {
  0x480F,
  0x400F,
  0x400F,
  0x400F,
  0x4010,
  0x3810,
  0x3810,
  0x3810,
  0x3810,
  0x3010,
  0x3010,
  0x3010,
  0x2810,
  0x2810,
  0x2810,
  0x2810,
  0x2010,
  0x2010,
  0x2010,
  0x1810,
  0x1810,
  0x1811,
  0x1811,
  0x1011,
  0x1011,
  0x1011,
  0x0811,
  0x0811,
  0x0811,
  0x0011,
  0x0011,
  0x0011,
  0x0011,
  0x0011,
  0x0031,
  0x0031,
  0x0051,
  0x0072,
  0x0072,
  0x0092,
  0x00B2,
  0x00B2,
  0x00D2,
  0x00F2,
  0x00F2,
  0x0112,
  0x0132,
  0x0152,
  0x0152,
  0x0172,
  0x0192,
  0x0192,
  0x01B2,
  0x01D2,
  0x01F3,
  0x01F3,
  0x0213,
  0x0233,
  0x0253,
  0x0253,
  0x0273,
  0x0293,
  0x02B3,
  0x02D3,
  0x02D3,
  0x02F3,
  0x0313,
  0x0333,
  0x0333,
  0x0353,
  0x0373,
  0x0394,
  0x03B4,
  0x03D4,
  0x03D4,
  0x03F4,
  0x0414,
  0x0434,
  0x0454,
  0x0474,
  0x0474,
  0x0494,
  0x04B4,
  0x04D4,
  0x04F4,
  0x0514,
  0x0534,
  0x0534,
  0x0554,
  0x0554,
  0x0574,
  0x0574,
  0x0573,
  0x0573,
  0x0573,
  0x0572,
  0x0572,
  0x0572,
  0x0571,
  0x0591,
  0x0591,
  0x0590,
  0x0590,
  0x058F,
  0x058F,
  0x058F,
  0x058E,
  0x05AE,
  0x05AE,
  0x05AD,
  0x05AD,
  0x05AD,
  0x05AC,
  0x05AC,
  0x05AB,
  0x05CB,
  0x05CB,
  0x05CA,
  0x05CA,
  0x05CA,
  0x05C9,
  0x05C9,
  0x05C8,
  0x05E8,
  0x05E8,
  0x05E7,
  0x05E7,
  0x05E6,
  0x05E6,
  0x05E6,
  0x05E5,
  0x05E5,
  0x0604,
  0x0604,
  0x0604,
  0x0603,
  0x0603,
  0x0602,
  0x0602,
  0x0601,
  0x0621,
  0x0621,
  0x0620,
  0x0620,
  0x0620,
  0x0620,
  0x0E20,
  0x0E20,
  0x0E40,
  0x1640,
  0x1640,
  0x1E40,
  0x1E40,
  0x2640,
  0x2640,
  0x2E40,
  0x2E60,
  0x3660,
  0x3660,
  0x3E60,
  0x3E60,
  0x3E60,
  0x4660,
  0x4660,
  0x4E60,
  0x4E80,
  0x5680,
  0x5680,
  0x5E80,
  0x5E80,
  0x6680,
  0x6680,
  0x6E80,
  0x6EA0,
  0x76A0,
  0x76A0,
  0x7EA0,
  0x7EA0,
  0x86A0,
  0x86A0,
  0x8EA0,
  0x8EC0,
  0x96C0,
  0x96C0,
  0x9EC0,
  0x9EC0,
  0xA6C0,
  0xAEC0,
  0xAEC0,
  0xB6E0,
  0xB6E0,
  0xBEE0,
  0xBEE0,
  0xC6E0,
  0xC6E0,
  0xCEE0,
  0xCEE0,
  0xD6E0,
  0xD700,
  0xDF00,
  0xDEE0,
  0xDEC0,
  0xDEA0,
  0xDE80,
  0xDE80,
  0xE660,
  0xE640,
  0xE620,
  0xE600,
  0xE5E0,
  0xE5C0,
  0xE5A0,
  0xE580,
  0xE560,
  0xE540,
  0xE520,
  0xE500,
  0xE4E0,
  0xE4C0,
  0xE4A0,
  0xE480,
  0xE460,
  0xEC40,
  0xEC20,
  0xEC00,
  0xEBE0,
  0xEBC0,
  0xEBA0,
  0xEB80,
  0xEB60,
  0xEB40,
  0xEB20,
  0xEB00,
  0xEAE0,
  0xEAC0,
  0xEAA0,
  0xEA80,
  0xEA60,
  0xEA40,
  0xF220,
  0xF200,
  0xF1E0,
  0xF1C0,
  0xF1A0,
  0xF180,
  0xF160,
  0xF140,
  0xF100,
  0xF0E0,
  0xF0C0,
  0xF0A0,
  0xF080,
  0xF060,
  0xF040,
  0xF020,
  0xF800,
};

uint16_t displayPixelWidth, displayPixelHeight;

void setup() {
  displayPixelWidth = 240 / (32 - 2);
  displayPixelHeight = 240 / (24);

  tft.init(TFT_W, TFT_H);  // Init ST7789 240x240
  // SPI speed defaults to SPI_DEFAULT_FREQ defined in the library, you can override it here
  // Note that speed allowable depends on chip and quality of wiring, if you go too fast, you
  // may end up with a black screen some times, or all the time.
  //tft.setSPISpeed(40000000);

  tft.fillScreen(ST77XX_BLACK);

  if (!mlx.begin(MLX90640_I2CADDR_DEFAULT, &Wire)) {
    tft.fillScreen(ST77XX_BLACK);
    tft.setCursor(0, 0);
    tft.setTextColor(ST77XX_RED);
    tft.setTextWrap(true);
    tft.setTextSize(4);
    tft.println("MLX90640 not found!");
    while (1) delay(10);
  }

  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_WHITE);
  tft.setCursor(0, 0);
  tft.setTextWrap(true);
  tft.setTextSize(2);

  tft.println("Found Adafruit MLX90640");
  tft.print("Serial number: ");
  tft.print(mlx.serialNumber[0], HEX);
  tft.print(mlx.serialNumber[1], HEX);
  tft.println(mlx.serialNumber[2], HEX);

  delay(5000);

  //mlx.setMode(MLX90640_INTERLEAVED);
  mlx.setMode(MLX90640_CHESS);
  tft.print("Current mode: ");
  if (mlx.getMode() == MLX90640_CHESS) {
    tft.println("Chess");
  } else {
    tft.println("Interleave");
  }

  mlx.setResolution(MLX90640_ADC_18BIT);
  tft.print("Current resolution: ");
  mlx90640_resolution_t res = mlx.getResolution();
  switch (res) {
    case MLX90640_ADC_16BIT: tft.println("16 bit"); break;
    case MLX90640_ADC_17BIT: tft.println("17 bit"); break;
    case MLX90640_ADC_18BIT: tft.println("18 bit"); break;
    case MLX90640_ADC_19BIT: tft.println("19 bit"); break;
  }

  mlx.setRefreshRate(MLX90640_2_HZ);
  tft.print("Current frame rate: ");
  mlx90640_refreshrate_t rate = mlx.getRefreshRate();
  switch (rate) {
    case MLX90640_0_5_HZ: tft.println("0.5 Hz"); break;
    case MLX90640_1_HZ: tft.println("1 Hz"); break;
    case MLX90640_2_HZ: tft.println("2 Hz"); break;
    case MLX90640_4_HZ: tft.println("4 Hz"); break;
    case MLX90640_8_HZ: tft.println("8 Hz"); break;
    case MLX90640_16_HZ: tft.println("16 Hz"); break;
    case MLX90640_32_HZ: tft.println("32 Hz"); break;
    case MLX90640_64_HZ: tft.println("64 Hz"); break;
  }

  delay(5000);

  // line draw test
  testlines(ST77XX_YELLOW);
  delay(500);

  tft.fillScreen(ST77XX_BLACK);
}

void loop() {
  uint32_t timestamp = millis();
  if (mlx.getFrame(frame) != 0) {
    tft.fillScreen(ST77XX_BLACK);
    tft.setCursor(0, 0);
    tft.setTextColor(ST77XX_YELLOW);
    tft.setTextWrap(true);
    tft.setTextSize(4);
    tft.println("Failed");
    return;
  }

  int colorTemp;
  for (uint8_t h = MLX_READ_Y_MIN; h < MLX_READ_Y_MAX; h++) {
    for (uint8_t w = MLX_READ_X_MIN; w < MLX_READ_X_MAX; w++) {
      float t = frame[h * MLX_W + w];

      t = min(t, MAXTEMP);
      t = max(t, MINTEMP);

      uint16_t colorIndex = map(t, MINTEMP, MAXTEMP, 0, 255);

      colorIndex = constrain(colorIndex, 0, 255);
      //draw the pixels!
      tft.fillRect(
        displayPixelWidth * w,
        displayPixelHeight * h,
        displayPixelWidth,
        displayPixelHeight,
        camColors[colorIndex]);
    }
  }

  delay(500);
}

void testlines(uint16_t color) {
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x = 0; x < tft.width(); x += 6) {
    tft.drawLine(0, tft.height() - 1, x, 0, color);
    delay(0);
  }
  for (int16_t y = 0; y < tft.height(); y += 6) {
    tft.drawLine(0, tft.height() - 1, tft.width() - 1, y, color);
    delay(0);
  }
}
