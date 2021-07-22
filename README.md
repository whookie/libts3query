# TS3Query - C++
This library is intended to enable easier access to TeamSpeak ServerQuery using C++.

## Prerequisites
The following libraries and packages are **required**:
- make
- cmake
- gtest
- gmock

The following libraries and packages are **optional**:
- valgrind

## Installation
- Clone the repository:
```
git clone git@github.com:WhOoKie/libts3query.git
cd libts3query
```

- Create a build directory:
```
mkdir build
cd build
```

- Build the library
```
cmake ..
make
```

- (Run unittests)
```
./ts3query_test # Run unittests
ctest -T memcheck # Run check for memory leaks, may require valgrind
```

- Install the library
```
sudo make install
```

## Documentation
None yet, but examples can be found in [the examples subdirectory](/examples)
