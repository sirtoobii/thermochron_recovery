#include <OneWire.h>

OneWire ibutton (7); // iButton connected on PIN 7.

byte addr[8];

byte READ_MEMORY = 0x69;
byte TA1_MEMORY = 0x00;
byte TA2_MEMORY = 0x10;
byte PASSWORD[8] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};

void setup(){
  Serial.begin(115200);
  Serial.println("Initialized, starting in 3 seconds...");
  delay(3);
}

void loop(){
  // Search for an iButton and assign the value to the addr if found.
  if (!ibutton.search (addr)){
     ibutton.reset_search();
     delay(250);
     return;
  }
  // At this point an iButton is found
  Serial.println("1-Wire Device Detected, ID is:");

  // Print ID
  for (int x = 0; x<8; x++){
    Serial.print(addr[x],HEX);
    Serial.print(" ");
  }
  Serial.print("\n");
  delay(1000);
  ibutton.reset();
  ibutton.select(addr);
  ibutton.write(READ_MEMORY);
  ibutton.write(TA1_MEMORY);
  ibutton.write(TA2_MEMORY);
  ibutton.write_bytes(PASSWORD,8);

  Serial.println("-----begin dump----");
  for(int i=0;i<0xff;i++){
    //32Byte for data, 2 Byte for CRC-16
    for(int j=0;j<34;j++){
          Serial.print(ibutton.read(), HEX);
          Serial.print(' ');
    }
    Serial.println();
  }
  Serial.println("-----end dump----");

  Serial.println("Done.\n\n");
  delay(100000);
}