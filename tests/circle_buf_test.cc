/*
* Brian R Taylor
* brian.taylor@bolderflight.com
* 
* Copyright (c) 2020 Bolder Flight Systems
*/

#include "circle_buf/circle_buf.h"
#include "gtest/gtest.h"

/* Test null pointers */
TEST(CircleBuff, NullPtrWrite) {
  CircularBuffer<uint8_t, 100> buff;
  std::size_t bytes_written = buff.Write(nullptr, 0);
  std::size_t bytes_read = buff.Read(nullptr, 0);
  EXPECT_EQ(0, bytes_written);
  EXPECT_EQ(0, bytes_read);
}
/* Test 0 length */
TEST(CircleBuff, ZeroLen) {
  CircularBuffer<uint8_t, 100> buff;
  uint8_t data[0];
  std::size_t bytes_written = buff.Write(data, sizeof(data));
  std::size_t bytes_read = buff.Read(data, sizeof(data));
  EXPECT_EQ(0, bytes_written);
  EXPECT_EQ(0, bytes_read);
}
/* Test expected results */
TEST(CircleBuff, Expected) {
  CircularBuffer<uint8_t, 10> buff;
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
