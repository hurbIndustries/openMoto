void checkSerial() {
  if(Serial.available()) {
    String data = Serial.readString();
    if(data == "bt") {
      if(bt_stat) {
        bt_stateChange = true;
        Serial.println("Bluetooth test off");
      } else {
        bt_stateChange = true;
        Serial.println("Bluetooth test on;");
      }
    } else
    if(data == "blTime") {
      if(mfd_night) {
        Serial.println("Setting MFD to Day...");
        mfd_brt = mfd_dayBrt;
        mfd_night = false;
       } else {
        Serial.println("Setting MFD to Night...");
        mfd_brt = mfd_nightBrt;
        mfd_night = true;
       }
    } else 
    if(data == "blIncr") {
      mfd_brt = mfd_brt + 20;
    } else 
    if(data == "blDecr") {
      mfd_brt = mfd_brt - 20;
    } else
    if(data == "l") {
      left();
    } else 
    if(data == "r") {
      right();
    }
  }
}