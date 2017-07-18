# simple-chess

[![Build Status](https://travis-ci.org/striezel/simple-chess.svg)](https://travis-ci.org/striezel/simple-chess)

simple-chess is (or better: will be) a small command-line tool that can be used
to perform some chess-related tasks. More information will follow soon.

## Building from source

### Prerequisites

To build simple-chess from source you need a C++ compiler with C++11 support,
CMake 3.0 or later, the libmongo-client-dev library and catch for unit tests.
It also helps to have Git, a distributed version control system, on your build
system to get the latest source code directly from the Git repository.

All that can usually be installed be typing

    apt-get install cmake g++ git libmongo-client-dev catch

or

    yum install cmake gcc-c++ git libmongo-client-devel catch

into a root terminal.

### Getting the source code

Get the source directly from Git by cloning the Git repository and change to
the directory after the repository is completely cloned:

    git clone https://github.com/striezel/simple-chess.git ./simple-chess
    cd simple-chess

### Build process

The build process is relatively easy, because CMake does all the preparations.
Starting in the root directory of the source, you can do the following steps:

    mkdir build
    cd build
    cmake ../
    make pmdb -j4

Now the binaries are built and ready for use.

## Copyright and Licensing

Copyright 2016-2017 Dirk Stolle

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
