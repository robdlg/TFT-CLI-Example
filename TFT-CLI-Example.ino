// Google AI Overview for "arduino simplecli background and text colors lcd commands"
// "Complete Example Sketch (SimpleCLI + TFT Display)"
// MIT License

#include <SimpleCLI.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> 
#include <SPI.h>

// Define T-Dongle-S3 Display pins
// ESP32-S3 GPIO
#define TFT_CS    4
#define TFT_RST   1
#define TFT_DC    2
#define TFT_MOSI  3
#define TFT_SCLK  5
#define TFT_BL    38

// Initialize Adafruit ST7735 over hardware/software SPI
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

SimpleCLI cli;

// Create a command variable
Command colorCmd;

// Helper function to map a string input to a 16-bit hex color
uint16_t getColorFromString(String colorName) {
    colorName.toLowerCase();
    if (colorName == "black")   return 0x0000;
    if (colorName == "blue")    return 0x001F;
    if (colorName == "red")     return 0xF800;
    if (colorName == "green")   return 0x07E0;
    if (colorName == "cyan")    return 0x07FF;
    if (colorName == "magenta") return 0xF81F;
    if (colorName == "yellow")  return 0xFFE0;
    return 0xFFFF; // Default to White
}

// Callback function executed when the command runs
void colorCallback(cmd* c) {
    Command reqCmd(c); // Wrap the pointer into a Command object

    // Extract the argument values from the CLI
    Argument bgArg  = reqCmd.getArgument("bg");
    Argument txtArg = reqCmd.getArgument("txt");

    // Change Background if specified
    if (bgArg.isSet()) {
        uint16_t bgColor = getColorFromString(bgArg.getValue());
        tft.fillScreen(bgColor);
        Serial.print("Background set to: ");
        Serial.println(bgArg.getValue());
    }

    // Change Text Color if specified
    if (txtArg.isSet()) {
        uint16_t txtColor = getColorFromString(txtArg.getValue());
        tft.setTextColor(txtColor);
        Serial.print("Text color set to: ");
        Serial.println(txtArg.getValue());
    }

    // Reprint sample text to show changes
    tft.setCursor(10, 50);
    tft.setTextSize(2);
    tft.println("Colors Updated!");
}

void setup() {
    Serial.begin(9600);
    
  // Turn on the backlight
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, LOW);

  // Initialize display for 80x160 ST7735
  tft.initR(INITR_MINI160x80_PLUGIN); 
  tft.setRotation(1); // Adjust rotation as needed (0 - 3)
  
  tft.fillScreen(ST7735_BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(1);
  tft.println("T-Dongle-S3 ready!");

    // Define the CLI command: "color -bg <value> -txt <value>"
    colorCmd = cli.addCommand("color", colorCallback);
    colorCmd.addArgument("bg");  // Add background argument
    colorCmd.addArgument("txt"); // Add text argument

    Serial.println("CLI Ready. Try typing: color -bg red -txt yellow");
}

void loop() {
    // Listen for Serial data and pass it to SimpleCLI
    if (Serial.available()) {
        String input = Serial.readStringUntil('\n');
        input.trim();
        cli.parse(input); // Triggers colorCallback if "color" is matched
    }
}
