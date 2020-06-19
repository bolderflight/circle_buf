/*
* Brian R Taylor
* brian.taylor@bolderflight.com
* 
* Copyright (c) 2020 Bolder Flight Systems
*/

#ifndef INCLUDE_CIRCLE_BUF_CIRCLE_BUF_H_
#define INCLUDE_CIRCLE_BUF_CIRCLE_BUF_H_

#include <string.h>
#include <array>
#include <algorithm>
#include <cstdint>

template<std::size_t ARRAY_SIZE>
class CircularBuffer {
 public:
  std::size_t Write(uint8_t *data, std::size_t bytes) {
    if ((bytes == 0) || (!data)) return 0;
    std::size_t bytes_to_write = std::min(bytes, capacity_ - size_);
    std::size_t space_avail = capacity_ - end_index_;
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
  std::size_t Read(uint8_t *data, std::size_t bytes) {
    if ((bytes == 0) || (!data)) return 0;
    std::size_t bytes_to_read = std::min(bytes, size_);
    std::size_t space_avail = capacity_ - begin_index_;
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
  std::size_t Size() {
    return size_;
  }
  std::size_t Capacity() {
    return capacity_;
  }

 private:
  std::array<uint8_t, ARRAY_SIZE> buffer_;
  std::size_t begin_index_ = 0;
  std::size_t end_index_ = 0;
  std::size_t capacity_ = ARRAY_SIZE;
  std::size_t size_ = 0;
};

#endif  // INCLUDE_CIRCLE_BUF_CIRCLE_BUF_H_
