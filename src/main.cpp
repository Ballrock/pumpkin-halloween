#include <Arduino.h>

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#ifndef PSTR
#define PSTR // Make Arduino Due happy
#endif

#define PIN_LED 13

// Globals
static uint16_t GREEN_COLOR = Adafruit_NeoMatrix::Color(34, 129, 1);
static uint16_t ORANGE1_COLOR = Adafruit_NeoMatrix::Color(248, 148, 7);
static uint16_t ORANGE2_COLOR = Adafruit_NeoMatrix::Color(242, 115, 28);
static uint16_t WHITE_COLOR = Adafruit_NeoMatrix::Color(255, 255, 255);

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(32, 8, 1, 3, PIN_LED,
                                               NEO_MATRIX_BOTTOM + NEO_MATRIX_RIGHT + NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG + NEO_TILE_BOTTOM + NEO_TILE_RIGHT + NEO_TILE_ZIGZAG + NEO_TILE_COLUMNS,
                                               NEO_GRB + NEO_KHZ800);

static int PUMPKIN[24][32] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 3, 3, 3, 1, 3, 3, 3, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 3, 2, 2, 2, 3, 0, 2, 2, 0, 2, 2, 0, 3, 2, 2, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 2, 3, 2, 2, 2, 3, 0, 2, 2, 2, 0, 2, 2, 2, 0, 3, 2, 2, 2, 3, 2, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 2, 3, 2, 2, 2, 3, 3, 0, 2, 2, 2, 0, 2, 2, 2, 0, 3, 3, 2, 2, 2, 3, 2, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 2, 3, 2, 2, 2, 3, 2, 2, 2, 2, 3, 2, 3, 2, 2, 2, 2, 3, 2, 2, 2, 3, 2, 0, 0, 0, 0, 0},
    {0, 0, 0, 2, 2, 0, 0, 0, 0, 3, 2, 2, 2, 3, 2, 2, 2, 3, 2, 2, 2, 3, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0},
    {0, 0, 0, 2, 3, 2, 0, 0, 0, 0, 0, 0, 3, 3, 2, 2, 2, 3, 3, 0, 0, 0, 0, 0, 0, 2, 3, 2, 0, 0, 0, 0},
    {0, 0, 0, 2, 3, 2, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 2, 3, 2, 0, 0, 0, 0},
    {0, 0, 0, 2, 3, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 3, 2, 0, 0, 0, 0},
    {0, 0, 0, 2, 3, 2, 2, 0, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 0, 0, 2, 2, 3, 2, 0, 0, 0, 0},
    {0, 0, 0, 2, 3, 2, 2, 2, 0, 0, 0, 0, 3, 2, 0, 0, 0, 2, 3, 0, 0, 0, 0, 2, 2, 2, 3, 2, 0, 0, 0, 0},
    {0, 0, 0, 2, 3, 2, 2, 2, 3, 2, 2, 2, 3, 3, 2, 2, 2, 3, 3, 2, 2, 2, 3, 2, 2, 2, 3, 2, 0, 0, 0, 0},
    {0, 0, 0, 2, 2, 3, 2, 2, 0, 3, 2, 2, 2, 3, 2, 0, 2, 3, 2, 2, 2, 3, 0, 2, 2, 3, 2, 2, 0, 0, 0, 0},
    {0, 0, 0, 0, 2, 3, 2, 0, 0, 0, 2, 2, 2, 3, 0, 0, 0, 3, 2, 2, 2, 0, 0, 0, 2, 3, 2, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 2, 2, 0, 0, 2, 0, 0, 2, 2, 0, 0, 2, 0, 0, 2, 2, 0, 0, 2, 0, 0, 2, 2, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 2, 3, 2, 2, 2, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 2, 2, 2, 3, 2, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 3, 2, 2, 2, 0, 0, 2, 3, 2, 3, 2, 0, 0, 2, 2, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 3, 3, 2, 2, 0, 2, 2, 3, 3, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

static int PUMPKIN_MOUTH[24][32] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 3, 3, 3, 1, 3, 3, 3, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 3, 2, 2, 2, 3, 0, 2, 2, 0, 2, 2, 0, 3, 2, 2, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 2, 3, 2, 2, 2, 3, 0, 2, 2, 2, 0, 2, 2, 2, 0, 3, 2, 2, 2, 3, 2, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 2, 3, 2, 2, 2, 3, 3, 0, 2, 2, 2, 0, 2, 2, 2, 0, 3, 3, 2, 2, 2, 3, 2, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 2, 3, 2, 2, 2, 3, 2, 2, 2, 2, 3, 2, 3, 2, 2, 2, 2, 3, 2, 2, 2, 3, 2, 0, 0, 0, 0, 0},
    {0, 0, 0, 2, 2, 0, 0, 0, 0, 3, 2, 2, 2, 3, 2, 2, 2, 3, 2, 2, 2, 3, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0},
    {0, 0, 0, 2, 3, 2, 0, 0, 0, 0, 0, 0, 3, 3, 2, 2, 2, 3, 3, 0, 0, 0, 0, 0, 0, 2, 3, 2, 0, 0, 0, 0},
    {0, 0, 0, 2, 3, 2, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 2, 3, 2, 0, 0, 0, 0},
    {0, 0, 0, 2, 3, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 3, 2, 0, 0, 0, 0},
    {0, 0, 0, 2, 3, 2, 2, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2, 2, 3, 2, 0, 0, 0, 0},
    {0, 0, 0, 2, 3, 2, 2, 2, 0, 0, 0, 0, 3, 2, 2, 2, 2, 2, 3, 0, 0, 0, 0, 2, 2, 2, 3, 2, 0, 0, 0, 0},
    {0, 0, 0, 2, 3, 2, 2, 2, 3, 3, 2, 2, 3, 3, 2, 0, 2, 3, 3, 2, 2, 3, 3, 2, 2, 2, 3, 2, 0, 0, 0, 0},
    {0, 0, 0, 2, 2, 3, 2, 3, 0, 0, 3, 2, 2, 3, 0, 0, 0, 3, 2, 2, 3, 0, 0, 3, 2, 3, 2, 2, 0, 0, 0, 0},
    {0, 0, 0, 0, 2, 3, 2, 0, 0, 0, 0, 2, 3, 0, 0, 0, 0, 0, 3, 2, 0, 0, 0, 0, 2, 3, 2, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 2, 3, 2, 2, 2, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 2, 2, 2, 3, 2, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 3, 2, 2, 2, 0, 0, 2, 3, 2, 3, 2, 0, 0, 2, 2, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 3, 3, 2, 2, 0, 2, 2, 3, 3, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

void displayPumpkin(Adafruit_NeoMatrix *matrix)
{
    for (int row = 0; row < 24; row++)
    {
        for (int column = 0; column < 32; column++)
        {
            switch (PUMPKIN[row][column])
            {
            case 1:
                matrix->drawPixel(column, row, GREEN_COLOR);
                break;
            case 2:
                matrix->drawPixel(column, row, ORANGE1_COLOR);
                break;
            case 3:
                matrix->drawPixel(column, row, ORANGE2_COLOR);
                break;
            case 4:
                matrix->drawPixel(column, row, WHITE_COLOR);
                break;
            }
        }
    }
}

void displayPumpkinMouth(Adafruit_NeoMatrix *matrix)
{
    for (int row = 0; row < 24; row++)
    {
        for (int column = 0; column < 32; column++)
        {
            switch (PUMPKIN[row][column])
            {
            case 1:
                matrix->drawPixel(column, row, GREEN_COLOR);
                break;
            case 2:
                matrix->drawPixel(column, row, ORANGE1_COLOR);
                break;
            case 3:
                matrix->drawPixel(column, row, ORANGE2_COLOR);
                break;
            case 4:
                matrix->drawPixel(column, row, WHITE_COLOR);
                break;
            }
        }
    }
}

void setup()
{
    Serial.begin(115200);

    while (!Serial)
    {
        ; // wait for serial port to connect.
    }

    Serial.println("Serial port ready.");

    // Start LED
    matrix.begin();
    matrix.fillScreen(Adafruit_NeoMatrix::Color(0, 0, 0));
    matrix.setBrightness(20);
    displayPumpkin(&matrix);

    // matrix.drawPixel(0, 0, ORANGE_COLOR);
    matrix.show();
}

void loop()
{
    while (true)
    {
        displayPumpkin(&matrix);
        matrix.show();
        delay(5000);
        // Laugh
        displayPumpkinMouth(&matrix);
        matrix.show();
        delay(200);
        displayPumpkin(&matrix);
        matrix.show();
        delay(200);
        displayPumpkinMouth(&matrix);
        matrix.show();
        delay(200);
        displayPumpkin(&matrix);
        matrix.show();
        delay(200);
        displayPumpkinMouth(&matrix);
        matrix.show();
        delay(200);
        displayPumpkin(&matrix);
        matrix.show();
        delay(200);
        displayPumpkinMouth(&matrix);
        matrix.show();
        delay(200);
        displayPumpkin(&matrix);
        matrix.show();
        delay(200);
    }
}