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
#include <iostream>

int main() {
  /* Create a 10 byte circular buffer */
  bfs::CircleBuf<uint8_t, 10> buff;
  std::cout << "Starting Capacity: " << buff.capacity() << std::endl;
  std::cout << "Starting Size: " << buff.size() << std::endl << std::endl;
  /* Write 5 bytes to it */
  std::cout << "Writing 1 - 5 to buffer..." << std::endl;
  uint8_t test[] = {1, 2, 3, 4, 5};
  unsigned int ret = buff.Write(test, sizeof(test));
  std::cout << "Bytes written: " << ret << std::endl;
  std::cout << "New Capacity: " << buff.capacity() << std::endl;
  std::cout << "New Size: " << buff.size() << std::endl;
  std::cout << std::endl;
  /* Read 3 bytes from buffer */
  std::cout << "Reading 3 bytes from buffer..." << std::endl;
  uint8_t read_val[20];
  ret = buff.Read(read_val, 3);
  std::cout << "Bytes read " << ret << std::endl;
  std::cout << "Bytes: " << std::endl;
  for (unsigned int i = 0; i < ret; i++) {
    std::cout << std::to_string(read_val[i]) << std::endl;
  }
  std::cout << std::endl;
  /* Try to write 10 bytes to buffer, only space for 8 */
  std::cout << "Writing 10 - 100 to buffer..." << std::endl;
  uint8_t test2[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
  ret = buff.Write(test2, sizeof(test2));
  std::cout << "Bytes written: " << ret << std::endl;
  std::cout << "New Capacity: " << buff.capacity() << std::endl;
  std::cout << "New Size: " << buff.size() << std::endl;
  std::cout << std::endl;
  /* Try to read 20 bytes from buffer, only 10 stored */
  std::cout << "Reading 20 bytes from buffer..." << std::endl;
  ret = buff.Read(read_val, sizeof(read_val));
  std::cout << "Bytes read " << ret << std::endl;
  std::cout << "Bytes: " << std::endl;
  for (unsigned int i = 0; i < ret; i++) {
    std::cout << std::to_string(read_val[i]) << std::endl;
  }
  std::cout << std::endl;
  /* Write 10 bytes to the buffer */
  std::cout << "Writing 10 - 100 to buffer, one at a time..." << std::endl;
  for (unsigned int i = 0; i < sizeof(test2); i++) {
    ret = buff.Write(test2[i]);
  }
  std::cout << "New Capacity: " << buff.capacity() << std::endl;
  std::cout << "New Size: " << buff.size() << std::endl;
  std::cout << std::endl;
  /* Read 5 bytes from the buffer */
  std::cout << "Reading 5 bytes from the buffer, one at a time..." << std::endl;
  std::cout << "Bytes: " << std::endl;
  for (unsigned int i = 0; i < 5; i++) {
    uint8_t val;
    bool ret = buff.Read(&val);
    if (ret) {
      std::cout << std::to_string(val) << std::endl;
    }
  }
  std::cout << "New Capacity: " << buff.capacity() << std::endl;
  std::cout << "New Size: " << buff.size() << std::endl;
  std::cout << std::endl;
  /* Clearing the buffer */
  std::cout << "Clearing the buffer..." << std::endl;
  buff.Clear();
  std::cout << "New Capacity: " << buff.capacity() << std::endl;
  std::cout << "New Size: " << buff.size() << std::endl; 
  std::cout << std::endl; 
}
