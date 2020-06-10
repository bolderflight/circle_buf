/*
* Brian R Taylor
* brian.taylor@bolderflight.com
* 
* Copyright (c) 2020 Bolder Flight Systems
*/

#ifndef INCLUDE_CIRCLE_BUF_CIRCLE_BUF_H_
#define INCLUDE_CIRCLE_BUF_CIRCLE_BUF_H_

#include <stdint.h>
#include <vector>

class CircularBuffer {
 public:
  explicit CircularBuffer(unsigned int size);
  unsigned int Write(const std::vector<uint8_t> &data);
  std::vector<uint8_t> Read(unsigned int bytes);
  unsigned int Size();
  unsigned int Capacity();

 private:
  std::vector<uint8_t> buffer_;
  unsigned int begin_index_ = 0;
  unsigned int end_index_ = 0;
  unsigned int capacity_ = 0;
  unsigned int size_ = 0;
};


#endif  // INCLUDE_CIRCLE_BUF_CIRCLE_BUF_H_
