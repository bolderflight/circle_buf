/*
* Brian R Taylor
* brian.taylor@bolderflight.com
* 
* Copyright (c) 2020 Bolder Flight Systems
*/

#include "circle_buf/circle_buf.h"
#include <iostream>

int main() {
  CircularBuffer buff(10);
  uint8_t test[5] = {1, 2, 3, 4, 5};
  unsigned int ret = buff.Write(test, sizeof(test));
  std::cout << ret << std::endl;
  std::cout << std::endl;
  uint8_t read_val[20];
  ret = buff.Read(read_val, 3);
  std::cout << ret << std::endl;
  std::cout << std::endl;
  for (unsigned int i = 0; i < ret; i++) {
    std::cout << std::to_string(read_val[i]) << std::endl;
  }
  std::cout << std::endl;
  uint8_t test2[10] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
  ret = buff.Write(test2, sizeof(test2));
  std::cout << ret << std::endl;
  std::cout << std::endl;
  ret = buff.Read(read_val, 20);
  std::cout << ret << std::endl;
  for (unsigned int i = 0; i < ret; i++) {
    std::cout << std::to_string(read_val[i]) << std::endl;
  }
}
