/*
* Brian R Taylor
* brian.taylor@bolderflight.com
* 
* Copyright (c) 2020 Bolder Flight Systems
*/

#include "circle_buf/circle_buf.h"
#include <iostream>

int main() {
  /* Create a 10 byte circular buffer */
  CircularBuffer<10> buff;
  std::cout << "Starting Capacity: " << buff.Capacity() << std::endl;
  std::cout << "Starting Size: " << buff.Size() << std::endl << std::endl;
  /* Write 5 bytes to it */
  std::cout << "Writing 1 - 5 to buffer..." << std::endl;
  uint8_t test[] = {1, 2, 3, 4, 5};
  unsigned int ret = buff.Write(test, sizeof(test));
  std::cout << "Bytes written: " << ret << std::endl;
  std::cout << "New Capacity: " << buff.Capacity() << std::endl;
  std::cout << "New Size: " << buff.Size() << std::endl;
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
  std::cout << "New Capacity: " << buff.Capacity() << std::endl;
  std::cout << "New Size: " << buff.Size() << std::endl;
  std::cout << std::endl;
  /* Try to read 20 bytes from buffer, only 10 stored */
  std::cout << "Reading 20 bytes from buffer..." << std::endl;
  ret = buff.Read(read_val, sizeof(read_val));
  std::cout << "Bytes read " << ret << std::endl;
  std::cout << "Bytes: " << std::endl;
  for (unsigned int i = 0; i < ret; i++) {
    std::cout << std::to_string(read_val[i]) << std::endl;
  }
}
