void setup() {
    Serial.begin(9600);

}

void loop() {
    int readVal = analogRead(A0);
    Serial.println(readVal);

} 
