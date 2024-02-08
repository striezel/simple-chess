#!/bin/sh

# Script to test executable when parameters are used in the wrong way.
#
#  Copyright (C) 2024  Dirk Stolle
#
#  This program is free software: you can redistribute it and/or modify
#  it under the terms of the GNU Lesser General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU Lesser General Public License for more details.
#
#  You should have received a copy of the GNU Lesser General Public License
#  along with this program.  If not, see <http://www.gnu.org/licenses/>.

# 1st parameter = executable path
if [ -z "$1" ]
then
  echo "First parameter must be executable file!"
  exit 1
fi

EXECUTABLE="$1"

# parameter --pgn given twice
"$EXECUTABLE" --pgn foo.pgn --pgn twice.pgn
if [ $? -ne 1 ]
then
  echo "Executable did not exit with code 1 when --pgn was given twice."
  exit 1
fi

# no file name after parameter --pgn
"$EXECUTABLE" --pgn
if [ $? -ne 1 ]
then
  echo "Executable did not exit with code 1 when --pgn had no file name."
  exit 1
fi

# no PNG file specified
"$EXECUTABLE"
if [ $? -ne 1 ]
then
  echo "Executable did not exit with code 1 when no PGN file was given."
  exit 1
fi

# non-existent PGN file
"$EXECUTABLE" --pgn does-not-exist.pgn
if [ $? -ne 2 ]
then
  echo "Executable did not exit with code 2 when PGN file did not exist."
  exit 1
fi

# parameter --delay given twice
"$EXECUTABLE" --pgn foo.pgn --delay 1 --delay 22
if [ $? -ne 1 ]
then
  echo "Executable did not exit with code 1 when --delay was given twice."
  exit 1
fi

# parameter --delay with non-integer value
"$EXECUTABLE" --pgn foo.pgn --delay blah
if [ $? -ne 1 ]
then
  echo "Executable did not exit with code 1 when --delay had non-int. value."
  exit 1
fi

# parameter --delay with negative value
"$EXECUTABLE" --pgn foo.pgn --delay -25
if [ $? -ne 1 ]
then
  echo "Executable did not exit with code 1 when --delay had negative value."
  exit 1
fi

# --letters is given twice
"$EXECUTABLE" --letters --letters
if [ $? -ne 1 ]
then
  echo "Executable did not exit with code 1 when --letters was given twice."
  exit 1
fi

# --symbols is given twice
"$EXECUTABLE" --symbols --symbols
if [ $? -ne 1 ]
then
  echo "Executable did not exit with code 1 when --symbols was given twice."
  exit 1
fi

# --meteor-chess on a version that does not support Meteor Chess
"$EXECUTABLE" --meteor-chess
if [ $? -ne 1 ]
then
  echo "Executable did not exit with code 1 when --meteor-chess was given."
  echo "Functionality related to Meteor Chess is not available in this build."
  exit 1
fi

# unknown parameter
"$EXECUTABLE" --this-is-not-supported
if [ $? -ne 1 ]
then
  echo "Executable did not exit with code 1 when an unknown parameter was given."
  exit 1
fi

exit 0
