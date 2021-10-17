#include <OneWire.h>
 
OneWire ibutton (7); // iButton connected on PIN 7.
 
byte addr[8];

byte READ_SCRATCHPAD = 0xaa;
byte WRITE_SCRATCHPAD = 0x0f;
byte TA1 = 0x00;
byte TA2 = 0x02;
byte ES = 0x1f;
byte data_bytes[10] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a};
 
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

  if ( ibutton.crc8( addr, 7) != addr[7]) {
    Serial.println("CRC is not valid!");
  }
  Serial.print("\n");
  delay(1000);
  ibutton.reset();
  ibutton.select(addr);
  ibutton.write(WRITE_SCATCHPAD);
  ibutton.write(TA1);
  ibutton.write(TA2);
  //write data to scratchpad (10 bytes)
  ibutton.write_bytes(data_bytes, 10);
  
  //pad till the end  (22 bytes)
  for(int i=0;i<22;i++){
    ibutton.write(0xff);
  }

  //Try to read scratchpad data
  ibutton.reset();
  ibutton.select(addr);
  ibutton.write(READ_SCRATCHPAD);
  Serial.print("TA1: ");
  Serial.println(ibutton.read(), HEX);
  Serial.print("TA2: ");
  Serial.println(ibutton.read(), HEX);  
  Serial.print("TA-E/S: ");
  Serial.println(ibutton.read(), HEX);
  delay(4000);

  Serial.print("Scrachpad data: ");

  for(int i=0;i<32;i++){
    Serial.print(ibutton.read(), HEX);
    Serial.print(' ');
  }

  Serial.println("Done.\n\n");
  delay(100000);
}