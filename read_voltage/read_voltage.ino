void setup() {
    Serial.begin(9600);

}

void loop() {
    int voltageValue = analogRead(A0);
    //voltageValue = (voltageValue / 1023.0) * 5.0;
    Serial.println(voltageValue);

}
