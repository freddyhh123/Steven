const int touchPin = 14; // Pin connected to the touch sensor
const int redLED = 12; // Pin connected to the red LED
const int amberLED = 33; // Pin connected to the amber LED
const int greenLED = 27; // Pin connected to the green LED
const int threshold = 25;
int touchValue;


void setup() {
  Serial.begin(115200);
  // Initialize the LED pins as outputs
  pinMode(redLED, OUTPUT);
  pinMode(amberLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(touchPin, INPUT);
}

void loop() {
    touchValue = touchRead(touchPin);
    Serial.println(touchValue);
  // Check if the touch sensor is activated
  if (touchValue < threshold){
    // Turn on the red LED
    digitalWrite(redLED, HIGH);
    delay(1000); // Keep it on for 1 seconds
    digitalWrite(redLED, LOW); // Turn off the red LED
    
    // Turn on the amber LED
    digitalWrite(amberLED, HIGH);
    delay(2000); // Keep it on for 2 seconds
    digitalWrite(amberLED, LOW); // Turn off the amber LED
    
    // Turn on the green LED
    digitalWrite(greenLED, HIGH);
    delay(1000); // Keep it on for 1 seconds
    digitalWrite(greenLED, LOW); // Turn off the green LED
    
    // After a single cycle, stop loop to avoid repeating.
    while(true) {
      // Do nothing infinite loop style
    }
  }
  // Add a small delay to prevent reading the touch sensor too rapidly
  delay(100);
}
