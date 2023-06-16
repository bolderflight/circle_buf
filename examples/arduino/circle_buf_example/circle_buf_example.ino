/*
* Brian R Taylor
* brian.taylor@bolderflight.com
* 
* Copyright (c) 2023 Bolder Flight Systems Inc
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the “Software”), to
* deal in the Software without restriction, including without limitation the
* rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
* sell copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
* IN THE SOFTWARE.
*/

#include "circle_buf.h"

void setup() {
  Serial.begin(115200);
  while (!Serial) {}
  /* Create a 10 byte circular buffer */
  bfs::CircleBuf<uint8_t, 10> buff;
  Serial.print("Starting Capacity: ");
  Serial.println(buff.capacity());
  Serial.print("Starting Size: ");
  Serial.println(buff.size());
  /* Write 5 bytes to it */
  Serial.println("Writing 1 - 5 to buffer...");
  uint8_t test[] = {1, 2, 3, 4, 5};
  int ret = buff.Write(test, sizeof(test));
  Serial.print("Bytes written: ");
  Serial.println(ret);
  Serial.print("New Capacity: ");
  Serial.println(buff.capacity());
  Serial.print("New Size: ");
  Serial.println(buff.size());
  /* Read 3 bytes from buffer */
  Serial.println("Reading 3 bytes from buffer...");
  uint8_t read_val[20];
  ret = buff.Read(read_val, 3);
  Serial.print("Bytes read: ");
  Serial.println(ret);
  Serial.println("Bytes:");
  for (int i = 0; i < ret; i++) {
    Serial.println(read_val[i]);
  }
  /* Try to write 10 bytes to buffer, only space for 8 */
  Serial.println("Writing 10 - 100 to buffer...");
  uint8_t test2[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
  ret = buff.Write(test2, sizeof(test2));
  Serial.print("Bytes written: ");
  Serial.println(ret);
  Serial.print("New Capacity: ");
  Serial.println(buff.capacity());
  Serial.print("New Size: ");
  Serial.println(buff.size());
  /* Try to read 20 bytes from buffer, only 10 stored */
  Serial.println("Reading 20 bytes from buffer...");
  ret = buff.Read(read_val, sizeof(read_val));
  Serial.print("Bytes read: ");
  Serial.println(ret);
  Serial.println("Bytes:");
  for (int i = 0; i < ret; i++) {
    Serial.println(read_val[i]);
  }
  /* Write 10 bytes to the buffer */
  Serial.println("Writing 10 - 100 to buffer, one at a time...");
  for (unsigned int i = 0; i < sizeof(test2); i++) {
    ret = buff.Write(test2[i]);
  }
  Serial.print("New Capacity: ");
  Serial.println(buff.capacity());
  Serial.print("New Size: ");
  Serial.println(buff.size());
  /* Read 5 bytes from the buffer */
  Serial.println("Reading 5 bytes from the buffer, one at a time...");
  Serial.println("Bytes:");
  for (unsigned int i = 0; i < 5; i++) {
    uint8_t val;
    bool ret = buff.Read(&val);
    if (ret) {
      Serial.println(val);
    }
  }
  Serial.print("New Capacity: ");
  Serial.println(buff.capacity());
  Serial.print("New Size: ");
  Serial.println(buff.size());
  /* Clearing the buffer */
  Serial.println("Clearing the buffer...");
  buff.Clear();
  Serial.print("New Capacity: ");
  Serial.println(buff.capacity());
  Serial.print("New Size: ");
  Serial.println(buff.size());
}


void loop() {}
