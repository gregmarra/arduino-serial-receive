/* 
 *  arduino-serial-receive
 *  by gregmarra
 *  
 *  This program receives a comma separated series of numbers from serial, and places them into an array.
 *  
 *  For example, sending "1,2,3,4\n" will update the array serialInputParams to contain [1,2,3,4]
 *  
 *  A few particular elements of this:
 *  * serialEvent – This default Arduino function receives and buffers a serial message.
 *  * strtok – Using this function to split the input
 *  * atoi – Converting character reprentations of numbers ("123") into ints (123)
 *  
 *  I found it difficult to get going with this, so I hope putting this up as an example will make this easier for others.
 *  
 */

#define SERIALINPUTBUFFERSIZE 64
char serialInputBuffer[SERIALINPUTBUFFERSIZE]; // hold incoming data
int serialInputBufferIndex = 0;
boolean serialInputComplete = false; // whether the input is complete

#define MAXSERIALINPUTPARAMS 4
int serialInputParams[MAXSERIALINPUTPARAMS];

void setup() {
  Serial.begin(9600);
}

void loop() {
  handleSerialInput(); 
}

void handleSerialInput() {
  if (serialInputComplete) {
    Serial.println(serialInputBuffer);
    splitCommand();
  
    memset(serialInputBuffer, 0, sizeof serialInputBuffer); // resets input buffer to 0's
  
    serialInputComplete = false;
  }
}

void splitCommand() {
  char* bufferPointer;
  bufferPointer = strtok(serialInputBuffer, ",");
  int serialInputParamsIndex = 0;
  
  while (bufferPointer != NULL)
  {
    Serial.println(atoi(bufferPointer));
    serialInputParams[serialInputParamsIndex++] = atoi(bufferPointer);
    bufferPointer = strtok(NULL, ",");
    
    if (serialInputParamsIndex >= MAXSERIALINPUTPARAMS) {
      break;
    }
  }
}

/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
void serialEvent() {
  while (Serial.available()) {
    serialInputBuffer[serialInputBufferIndex] = Serial.read();
    
    if (serialInputBuffer[serialInputBufferIndex] == '\n') {
      serialInputComplete = true;
      serialInputBufferIndex = 0;
    } else {
      serialInputBufferIndex++;
      if (serialInputBufferIndex >= SERIALINPUTBUFFERSIZE) {
        serialInputBufferIndex = SERIALINPUTBUFFERSIZE - 1; // avoid buffer overflows
      }
    }
  }
}

