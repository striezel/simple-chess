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

# parameter --meteor-chess given twice
"$EXECUTABLE" --meteor-chess --meteor-chess
if [ $? -ne 1 ]
then
  echo "Executable did not exit with code 1 when --meteor-chess was given twice."
  exit 1
fi

# no host name after parameter --hostname
"$EXECUTABLE" --hostname
if [ $? -ne 1 ]
then
  echo "Executable did not exit with code 1 when --hostname had no host name."
  exit 1
fi

# parameter --port given twice
"$EXECUTABLE" --pgn foo.pgn --meteor-chess --port 3001 --port 3002
if [ $? -ne 1 ]
then
  echo "Executable did not exit with code 1 when --port was given twice."
  exit 1
fi

# parameter --port with non-integer value
"$EXECUTABLE" --pgn foo.pgn --meteor-chess --port blah
if [ $? -ne 1 ]
then
  echo "Executable did not exit with code 1 when --port had non-int. value."
  exit 1
fi

# parameter --port with negative value
"$EXECUTABLE" --pgn foo.pgn --meteor-chess --port -25
if [ $? -ne 1 ]
then
  echo "Executable did not exit with code 1 when --port had negative value."
  exit 1
fi

# parameter --port with port zero
"$EXECUTABLE" --pgn foo.pgn --meteor-chess --port 0
if [ $? -ne 1 ]
then
  echo "Executable did not exit with code 1 when --port had value zero."
  exit 1
fi

# parameter --port with value that is too big
"$EXECUTABLE" --pgn foo.pgn --meteor-chess --port 34567
if [ $? -ne 1 ]
then
  echo "Executable did not exit with code 1 when --port had out of range value."
  exit 1
fi

exit 0
