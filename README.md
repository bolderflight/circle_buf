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

**CircularBuffer<typename T, std::size_t N>** Creates a circular buffer object, of type *T* with buffer size *N*.

```C++
/* Create a 10 byte circular buffer of uint8_t */
CircularBuffer<uint8_t, 10> buff;
```

**bool Write(T val)** Writes a single value to the buffer. Note the buffer prevents over-writing data. This method returns true on success or false on failure.

```C++
bool status = buff.Write(3);
```

**std::size_t Write(T &ast;data, std::size_t len)** Writes data into the buffer given a pointer to the data and the number of elements to write. Returns the number of elements written into the buffer. Note that the buffer prevents over-writing data, so the number of elements written may be less than the number of elements to write.

```C++
uint8_t test[] = {1, 2, 3, 4, 5};
std::size_t ret = buff.Write(test, sizeof(test));
```

**T Read()** Reads a single value from the buffer. If the buffer is empty, returns 0.

```C++
uint8_t val = buff.Read();
```

**std::size_t Read(T &ast;data, std::size_t len)** Reads elements from the buffer given a pointer to store the data and the maximum number of elements to read. Returns the number of elements read off the buffer.

```C++
uint8_t read_val[20];
std::size_t ret = buff.Read(read_val, sizeof(read_val));
```

**std::size_t Capacity()** Returns the capacity of the circular buffer. This will always be equal to *N* used during construction.

```C++
std::cout << buff.Capacity() << std::endl;
```

**std::size_t Size()** Returns the number of elements currently stored in the buffer.

```C++
std::cout << buff.Size() << std::endl;
```
