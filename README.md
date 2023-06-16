
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

![Bolder Flight Systems Logo](img/logo-words_75.png) &nbsp; &nbsp; ![Arduino Logo](img/arduino_logo_75.png)

# CircleBuf
This library implements a first in, first out [circular buffer](https://en.wikipedia.org/wiki/Circular_buffer), methods are provided for writing to and reading from the buffer. This library is compatible with Arduino and with CMake build systems.
   * [License](LICENSE.md)
   * [Changelog](CHANGELOG.md)
   * [Contributing guide](CONTRIBUTING.md)

# Installation

## Arduino
Use the Arduino Library Manager to install this library or clone to your Arduino/libraries folder. The library is added as:

```C++
#include "circle_buf.h"
```

An example Arduino executable is located at *examples/arduino/circle_buf_example/circle_buf_example.ino*. Teensy 3.x, 4.x, and LC devices are used for testing under Arduino and this library should be compatible with other devices.

## CMake
CMake is used to build this library, which is exported as a library target called *circle_buf*. The header is added as:

```C++
#include "circle_buf.h"
```

The library can be also be compiled stand-alone using the CMake idiom of creating a *build* directory and then, from within that directory issuing:

```
cmake ..
make
```

This will build the library, an example executable called *circle_buf_example*, and an executable for testing using the Google Test framework, called *circle_buf_test*. The example executable source file is located at *examples/cmake/circle_buf_example.cc*.

# Namespace
This library is within the namespace *bfs*

# CircleBuf
This class implements the circular buffer.

## Methods

**CircleBuf<typename T, std::size_t N>** Creates a circular buffer object, of type *T* with buffer size *N*.

```C++
/* Create a 10 byte circular buffer of uint8_t */
bfs::CircleBuf<uint8_t, 10> buff;
```

**bool Write(const T val)** Writes a single value to the buffer. Note the buffer prevents over-writing data. This method returns true on success or false on failure.

```C++
bool status = buff.Write(3);
```

**std::size_t Write(T const &ast; const data, const std::size_t len)** Writes data into the buffer given a pointer to the data and the number of elements to write. Returns the number of elements written into the buffer. Note that the buffer prevents over-writing data, so the number of elements written may be less than the number of elements to write.

```C++
uint8_t test[] = {1, 2, 3, 4, 5};
std::size_t ret = buff.Write(test, sizeof(test));
```

**bool Read(T &ast; const data)** Reads a single value from the buffer given a pointer to store the data. True is returned if a value is returned through the pointer. A value would not be returned if the buffer is empty (i.e size = 0).

```C++
uint8_t val;
bool ret = buff.Read(&val);
if (ret) {
   std::cout << std::to_string(val) << std::endl;
}
```

**std::size_t Read(T &ast; const data, std::size_t len)** Reads elements from the buffer given a pointer to store the data and the maximum number of elements to read. Returns the number of elements read off the buffer.

```C++
uint8_t read_val[20];
std::size_t ret = buff.Read(read_val, sizeof(read_val));
```

**std::size_t capacity()** Returns the capacity of the circular buffer. This will always be equal to *N* used during construction.

```C++
std::cout << buff.capacity() << std::endl;
```

**std::size_t size()** Returns the number of elements currently stored in the buffer.

```C++
std::cout << buff.size() << std::endl;
```

**void Clear()** Empties the buffer.

```C++
buff.Clear();
```
