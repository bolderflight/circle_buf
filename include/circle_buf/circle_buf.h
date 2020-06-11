/*
* Brian R Taylor
* brian.taylor@bolderflight.com
* 
* Copyright (c) 2020 Bolder Flight Systems
*/

#ifndef INCLUDE_CIRCLE_BUF_CIRCLE_BUF_H_
#define INCLUDE_CIRCLE_BUF_CIRCLE_BUF_H_

#include <stdint.h>
#include <string.h>
#include <array>
#include <algorithm>

template<unsigned int ARRAY_SIZE>
class CircularBuffer {
 public:
  unsigned int Write(uint8_t *data, unsigned int bytes) {
    if ((bytes == 0) || (!data)) return 0;
    unsigned int bytes_to_write = std::min(bytes, capacity_ - size_);
    unsigned int space_avail = capacity_ - end_index_;
    if (space_avail < bytes_to_write) {
      memcpy(buffer_.data() + end_index_, data, space_avail);
      memcpy(buffer_.data(), data + space_avail, bytes_to_write - space_avail);
      end_index_ = bytes_to_write - space_avail;
    } else {
      memcpy(buffer_.data() + end_index_, data, bytes_to_write);
      end_index_ += bytes_to_write;
    }
    size_ += bytes_to_write;
    return bytes_to_write;
  }
  unsigned int Read(uint8_t *data, unsigned int bytes) {
    if ((bytes == 0) || (!data)) return 0;
    unsigned int bytes_to_read = std::min(bytes, size_);
    unsigned int space_avail = capacity_ - begin_index_;
    if (space_avail < bytes_to_read) {
      memcpy(data, buffer_.data() + begin_index_, space_avail);
      memcpy(data + space_avail, buffer_.data(), bytes_to_read - space_avail);
      begin_index_ = bytes_to_read - space_avail;
    } else {
      memcpy(data, buffer_.data() + begin_index_, bytes_to_read);
      begin_index_ += bytes_to_read;
    }
    size_ -= bytes_to_read;
    return bytes_to_read;
  }
  unsigned int Size() {
    return size_;
  }
  unsigned int Capacity() {
    return capacity_;
  }

 private:
  std::array<uint8_t, ARRAY_SIZE> buffer_;
  unsigned int begin_index_ = 0;
  unsigned int end_index_ = 0;
  unsigned int capacity_ = ARRAY_SIZE;
  unsigned int size_ = 0;
};

#endif  // INCLUDE_CIRCLE_BUF_CIRCLE_BUF_H_
