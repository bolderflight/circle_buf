/*
* Brian R Taylor
* brian.taylor@bolderflight.com
* 
* Copyright (c) 2020 Bolder Flight Systems
*/

#include "circle_buf/circle_buf.h"
#include <vector>
#include <iostream>

int main() {
  CircularBuffer buff(10);
  std::vector<uint8_t> test = {1, 2, 3, 4, 5};
  unsigned int ret = buff.Write(test);
  std::cout << ret << std::endl;
  std::cout << std::endl;
  std::vector<uint8_t> read_val = buff.Read(3);
  std::cout << read_val.size() << std::endl;
  std::cout << std::endl;
  for (unsigned int i = 0; i < read_val.size(); i++) {
    std::cout << std::to_string(read_val[i]) << std::endl;
  }
  std::cout << std::endl;
  std::vector<uint8_t> test2 = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
  ret = buff.Write(test2);
  std::cout << ret << std::endl;
  std::cout << std::endl;
  read_val = buff.Read(20);
  std::cout << read_val.size() << std::endl;
  for (unsigned int i = 0; i < read_val.size(); i++) {
    std::cout << std::to_string(read_val[i]) << std::endl;
  }
}
