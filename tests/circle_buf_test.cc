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

#include "circle_buf/circle_buf.h"
#include "gtest/gtest.h"

/* Test null pointers */
TEST(CircleBuff, NullPtrWrite) {
  bfs::CircularBuffer<uint8_t, 100> buff;
  std::size_t bytes_written = buff.Write(nullptr, 0);
  std::size_t bytes_read = buff.Read(nullptr, 0);
  EXPECT_EQ(0, bytes_written);
  EXPECT_EQ(0, bytes_read);
}
/* Test 0 length */
TEST(CircleBuff, ZeroLen) {
  bfs::CircularBuffer<uint8_t, 100> buff;
  uint8_t data[0];
  std::size_t bytes_written = buff.Write(data, sizeof(data));
  std::size_t bytes_read = buff.Read(data, sizeof(data));
  EXPECT_EQ(0, bytes_written);
  EXPECT_EQ(0, bytes_read);
}
/* Test expected results */
TEST(CircleBuff, Expected) {
  bfs::CircularBuffer<uint8_t, 10> buff;
  uint8_t data[5];
  EXPECT_EQ(10, buff.Capacity());
  EXPECT_EQ(0, buff.Size());
  std::size_t bytes_written = buff.Write(data, sizeof(data));
  EXPECT_EQ(5, bytes_written);
  EXPECT_EQ(10, buff.Capacity());
  EXPECT_EQ(5, buff.Size());
  uint8_t read_val[20];
  std::size_t bytes_read = buff.Read(read_val, 3);
  EXPECT_EQ(3, bytes_read);
  EXPECT_EQ(10, buff.Capacity());
  EXPECT_EQ(2, buff.Size());
  uint8_t data2[10];
  bytes_written = buff.Write(data2, sizeof(data2));
  EXPECT_EQ(8, bytes_written);
  EXPECT_EQ(10, buff.Capacity());
  EXPECT_EQ(10, buff.Size());
  bytes_read = buff.Read(read_val, 20);
  EXPECT_EQ(10, bytes_read);
  EXPECT_EQ(10, buff.Capacity());
  EXPECT_EQ(0, buff.Size());
  for (int i = 0; i < 10; i++) {
    buff.Write(data2[i]);
  }
  EXPECT_EQ(10, buff.Capacity());
  EXPECT_EQ(10, buff.Size());
  for (int i = 0; i < 5; i++) {
    buff.Read();
  }
  EXPECT_EQ(10, buff.Capacity());
  EXPECT_EQ(5, buff.Size());
  buff.Clear();
  EXPECT_EQ(10, buff.Capacity());
  EXPECT_EQ(0, buff.Size());
}
