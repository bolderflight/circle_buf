/*
* Brian R Taylor
* brian.taylor@bolderflight.com
* 
* Copyright (c) 2021 Bolder Flight Systems Inc
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

#ifndef INCLUDE_CIRCLE_BUF_CIRCLE_BUF_H_
#define INCLUDE_CIRCLE_BUF_CIRCLE_BUF_H_

#include <string.h>
#include <array>
#include <algorithm>
#include <cstdint>

namespace bfs {

template<typename T, std::size_t N>
class CircularBuffer {
 public:
  bool Write(T val) {
    if (capacity_ - size_) {
      buffer_[end_index_] = val;
      end_index_ = (end_index_ + 1) % capacity_;
      size_++;
      return true;
    }
    return false;
  }
  std::size_t Write(T *data, std::size_t len) {
    if ((len == 0) || (!data)) return 0;
    std::size_t vals_to_write = std::min(len, capacity_ - size_);
    std::size_t space_avail = capacity_ - end_index_;
    if (space_avail < vals_to_write) {
      memcpy(buffer_.data() + end_index_, data, space_avail * sizeof(T));
      memcpy(buffer_.data(), data + space_avail,
            (vals_to_write - space_avail) * sizeof(T));
      end_index_ = vals_to_write - space_avail;
    } else {
      memcpy(buffer_.data() + end_index_, data, vals_to_write * sizeof(T));
      end_index_ += vals_to_write;
    }
    size_ += vals_to_write;
    return vals_to_write;
  }
  T Read() {
    if (size_) {
      T val = buffer_[begin_index_];
      begin_index_ = (begin_index_ + 1) % capacity_;
      size_--;
      return val;
    }
    return static_cast<T>(0);
  }
  std::size_t Read(T *data, std::size_t len) {
    if ((len == 0) || (!data)) return 0;
    std::size_t vals_to_read = std::min(len, size_);
    std::size_t space_avail = capacity_ - begin_index_;
    if (space_avail < vals_to_read) {
      memcpy(data, buffer_.data() + begin_index_, space_avail * sizeof(T));
      memcpy(data + space_avail, buffer_.data(),
            (vals_to_read - space_avail) * sizeof(T));
      begin_index_ = vals_to_read - space_avail;
    } else {
      memcpy(data, buffer_.data() + begin_index_, vals_to_read * sizeof(T));
      begin_index_ += vals_to_read;
    }
    size_ -= vals_to_read;
    return vals_to_read;
  }
  std::size_t Size() {
    return size_;
  }
  std::size_t Capacity() {
    return capacity_;
  }
  void Clear() {
    begin_index_ = 0;
    end_index_ = 0;
    size_ = 0;
  }

 private:
  std::array<T, N> buffer_;
  std::size_t begin_index_ = 0;
  std::size_t end_index_ = 0;
  std::size_t capacity_ = N;
  std::size_t size_ = 0;
};

}  // namespace bfs

#endif  // INCLUDE_CIRCLE_BUF_CIRCLE_BUF_H_
