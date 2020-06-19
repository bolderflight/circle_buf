# Circular buffer
This library implements a first in, first out [circular buffer](https://en.wikipedia.org/wiki/Circular_buffer), methods are providing for writing to and reading from the buffer.
   * [License](LICENSE.md)
   * [Changelog](CHANGELOG.md)
   * [Contributing guide](CONTRIBUTING.md)

## Installation
CMake is used to build this library, which is exported as a library target called *circle_buf*. The header is added as:

```
#include "circle_buf/circle_buf.h"
```
Note that you'll need CMake version 3.13 or above; it is recommended to build and install CMake from source, directions are located in the [CMake GitLab repository](https://github.com/Kitware/CMake).

The library can be also be compiled stand-alone using the CMake idiom of creating a *build* directory and then, from within that directory issuing:

```
cmake ..
make
```

This will build the library, an example executable called *circle_buf_example*, and an executable for testing using the Google Test framework, called *circle_buf_test*. The example executable source file is located at *examples/circle_buf_example.cc*. This code is built and tested on AARCH64 and AMD64 system running Linux and AMD64 systems running the Windows Subsystem for Linux (WSL).

# CircularBuffer
This class implements the circular buffer.

## Methods

**CircularBuffer<BUFFER_SIZE>** Creates a circular buffer object, with a buffer size given by BUFFER_SIZE in bytes.

```C++
/* Create a 10 byte circular buffer */
CircularBuffer<10> buff;
```

**std::size_t Write(uint8_t &ast;data, std::size_t bytes)** Writes data into the buffer given a pointer to the data and the number of bytes to write. Returns the number of bytes written into the buffer. Note that the buffer prevents over-writing data, so the number of bytes written may be less than the number of bytes to write.

```C++
uint8_t test[] = {1, 2, 3, 4, 5};
std::size_t ret = buff.Write(test, sizeof(test));
```

**std::size_t Read(uint8_t &ast;data, std::size_t bytes)** Reads bytes from the buffer given a pointer to store the data and the maximum number of bytes to read. Returns the number of bytes read off the buffer.

```C++
uint8_t read_val[20];
std::size_t ret = buff.Read(read_val, sizeof(read_val));
```

**std::size_t Capacity()** Returns the capacity of the circular buffer. This will always be equal to the BUFFER_SIZE used during construction.

```C++
std::cout << buff.Capacity() << std::endl;
```

**std::size_t Size()** Returns the number of bytes currently stored in the buffer.

```C++
std::cout << buff.Size() << std::endl;
```
