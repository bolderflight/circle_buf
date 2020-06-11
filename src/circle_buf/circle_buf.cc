/*
* Brian R Taylor
* brian.taylor@bolderflight.com
* 
* Copyright (c) 2020 Bolder Flight Systems
*/

#include "circle_buf/circle_buf.h"
#include <string.h>
#include <algorithm>

unsigned int CircularBuffer::Write(const std::vector<uint8_t> &data) {
  if (data.size() == 0) return 0;
  unsigned int bytes_to_write = std::min((unsigned int)data.size(), capacity_ - size_);
  unsigned int space_avail = capacity_ - end_index_;
  if (space_avail < bytes_to_write) {
    memcpy(buffer_.data() + end_index_, data.data(), space_avail);
    memcpy(buffer_.data(), data.data() + space_avail, bytes_to_write - space_avail);
    end_index_ = bytes_to_write - space_avail;
  } else {
    memcpy(buffer_.data() + end_index_, data.data(), bytes_to_write);
    end_index_ += bytes_to_write;
  }
  size_ += bytes_to_write;
  return bytes_to_write;
}

std::vector<uint8_t> CircularBuffer::Read(unsigned int bytes) {
  unsigned int bytes_to_read = std::min(bytes, size_);
  unsigned int space_avail = capacity_ - begin_index_;
  std::vector<uint8_t> ret(bytes_to_read);
  if (bytes == 0) return ret;
  if (space_avail < bytes_to_read) {
    memcpy(ret.data(), buffer_.data() + begin_index_, space_avail);
    memcpy(ret.data() + space_avail, buffer_.data(), bytes_to_read - space_avail);
    begin_index_ = bytes_to_read - space_avail;
  } else {
    memcpy(ret.data(), buffer_.data() + begin_index_, bytes_to_read);
    begin_index_ += bytes_to_read;
  }
  size_ -= bytes_to_read;
  return ret;
}

unsigned int CircularBuffer::Size() {
  return size_;
}

unsigned int CircularBuffer::Capacity() {
  return capacity_;
}
