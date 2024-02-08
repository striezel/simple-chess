# simple-chess

`simple-chess` provides a collection of a small command-line tools that can be
used to perform some chess-related tasks.

Currently, these are the following programs:

* [`simple-chess-engine`](./apps/engine/readme.md) - an XBoard-compatible chess
  engine that supports most of the XBoard commands from protocol version 2
* [`meteor-chess-client`](./apps/meteor-chess-client/readme.md) - utility tool
  for use with [Meteor Chess](https://github.com/striezel/meteor-chess), _still
  under development_
* [`pgn-reader`](./apps/pgn-reader/readme.md) - command-line application that
  parses a file containing a chess game in [Portable Game Notation](https://en.wikipedia.org/wiki/Portable_Game_Notation)
  and will then replay that game move by move
* [`simple-chess-cli`](./apps/simple-chess-cli/readme.md) - program that allows
  to play against the engine of `simple-chess`

## Build status

* GitHub Actions:
  [![GitHub CI Clang status](https://github.com/striezel/simple-chess/workflows/Clang/badge.svg)](https://github.com/striezel/simple-chess/actions)
  [![GitHub CI GCC status](https://github.com/striezel/simple-chess/workflows/GCC/badge.svg)](https://github.com/striezel/simple-chess/actions)
  [![GitHub CI MSVC status](https://github.com/striezel/simple-chess/workflows/MSVC/badge.svg)](https://github.com/striezel/simple-chess/actions)
  [![GitHub CI MSYS2 status](https://github.com/striezel/simple-chess/workflows/MSYS2/badge.svg)](https://github.com/striezel/simple-chess/actions)
* GitLab CI:
[![GitLab pipeline status](https://gitlab.com/striezel/simple-chess/badges/master/pipeline.svg)](https://gitlab.com/striezel/simple-chess/-/pipelines)

## Building from source

### Prerequisites

To build simple-chess from source you need a C++ compiler with C++17 support,
CMake 3.8 or later, the libmongo-client-dev library and catch for unit tests.
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
    make -j4

Now the binaries are built and ready for use.

## Copyright and Licensing

Copyright 2016, 2017, 2018, 2019, 2020, 2021, 2024  Dirk Stolle

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
