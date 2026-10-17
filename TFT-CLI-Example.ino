// Google AI Overview for "arduino simplecli background and text colors lcd commands"
// "Complete Example Sketch (SimpleCLI + TFT Display)"
// MIT License

#include <SimpleCLI.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <MCUFRIEND_kbv.h>   // Example TFT Display library (Change to your specific LCD library)

MCUFRIEND_kbv tft;
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
    
    // Initialize Display
    uint16_t ID = tft.readID();
    tft.begin(ID);
    tft.fillScreen(0x0000); // Start Black
    tft.setTextColor(0xFFFF); // Start White Text

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
