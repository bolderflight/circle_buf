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

#ifndef CIRCLE_BUF_SRC_CIRCLE_BUF_H_  // NOLINT
#define CIRCLE_BUF_SRC_CIRCLE_BUF_H_

#if defined(ARDUINO)
#include <Arduino.h>
#else
#include <cstring>
#include <cstddef>
#include <cstdint>
#include <algorithm>
#endif

namespace bfs {

template<typename T, size_t N>
class CircleBuf {
 public:
  bool Write(const T val) {
    if (capacity_ - size_) {
      buffer_[end_index_] = val;
      end_index_ = (end_index_ + 1) % capacity_;
      size_++;
      return true;
    }
    return false;
  }
  size_t Write(T const * const data, const size_t len) {
    if ((len == 0) || (!data)) return 0;
    #if defined(ARDUINO)
    vals_to_write_ = min(len, capacity_ - size_);
    #else
    vals_to_write_ = std::min(len, capacity_ - size_);
    #endif
    space_avail_ = capacity_ - end_index_;
    if (space_avail_ < vals_to_write_) {
      memcpy(buffer_ + end_index_, data, space_avail_ * sizeof(T));
      memcpy(buffer_, data + space_avail_,
            (vals_to_write_ - space_avail_) * sizeof(T));
      end_index_ = vals_to_write_ - space_avail_;
    } else {
      memcpy(buffer_ + end_index_, data, vals_to_write_ * sizeof(T));
      end_index_ += vals_to_write_;
    }
    size_ += vals_to_write_;
    return vals_to_write_;
  }
  bool Read(T * const data) {
    if (!data) {return false;}
    if (size_) {
      *data = buffer_[begin_index_];
      begin_index_ = (begin_index_ + 1) % capacity_;
      size_--;
    }
    return true;
  }
  size_t Read(T * const data, const size_t len) {
    if ((len == 0) || (!data)) return 0;
    #if defined(ARDUINO)
    vals_to_read_ = min(len, size_);
    #else
    vals_to_read_ = std::min(len, size_);
    #endif
    space_avail_ = capacity_ - begin_index_;
    if (space_avail_ < vals_to_read_) {
      memcpy(data, buffer_ + begin_index_, space_avail_ * sizeof(T));
      memcpy(data + space_avail_, buffer_,
            (vals_to_read_ - space_avail_) * sizeof(T));
      begin_index_ = vals_to_read_ - space_avail_;
    } else {
      memcpy(data, buffer_ + begin_index_, vals_to_read_ * sizeof(T));
      begin_index_ += vals_to_read_;
    }
    size_ -= vals_to_read_;
    return vals_to_read_;
  }
  inline size_t size() const {return size_;}
  inline size_t capacity() const {return capacity_;}
  void Clear() {
    begin_index_ = 0;
    end_index_ = 0;
    size_ = 0;
  }

 private:
  T buffer_[N];
  size_t begin_index_ = 0;
  size_t end_index_ = 0;
  size_t capacity_ = N;
  size_t size_ = 0;
  size_t vals_to_write_, vals_to_read_, space_avail_;
};

}  // namespace bfs

#endif  // CIRCLE_BUF_SRC_CIRCLE_BUF_H_ NOLINT
