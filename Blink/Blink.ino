int buttonState = 0;
void setup() {
    // initialize digital pin LED_BUILTIN as an output.
    pinMode(10, OUTPUT);
    pinMode(11, INPUT);
}

// the loop function runs over and over again forever
void loop() {
    buttonState = digitalRead(11);
    if(buttonState == 1){
        digitalWrite(10, HIGH);
    }else if(buttonState == 0){
        digitalWrite(10, LOW);
    }
}
