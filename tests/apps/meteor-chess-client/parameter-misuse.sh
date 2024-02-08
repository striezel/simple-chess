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

# parameter --board given twice
"$EXECUTABLE" --board foo --board foo
if [ $? -ne 1 ]
then
  echo "Executable did not exit with code 1 when --board was given twice."
  exit 1
fi

# no board ID after parameter --board
"$EXECUTABLE" --board
if [ $? -ne 1 ]
then
  echo "Executable did not exit with code 1 when --board had no board ID."
  exit 1
fi

# no board ID at all
"$EXECUTABLE"
if [ $? -ne 1 ]
then
  echo "Executable did not exit with code 1 no board ID was specified."
  exit 1
fi

# parameter --hostname given twice
"$EXECUTABLE" --hostname node.local --hostname node2.local
if [ $? -ne 1 ]
then
  echo "Executable did not exit with code 1 when --hostname was given twice."
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
"$EXECUTABLE" --board aBcDeFg1234 --port 3001 --port 3002
if [ $? -ne 1 ]
then
  echo "Executable did not exit with code 1 when --port was given twice."
  exit 1
fi

# parameter --port with non-integer value
"$EXECUTABLE" --board aBcDeFg1234 --port blah
if [ $? -ne 1 ]
then
  echo "Executable did not exit with code 1 when --port had non-int. value."
  exit 1
fi

# parameter --port with negative value
"$EXECUTABLE" --board aBcDeFg1234 --port -123
if [ $? -ne 1 ]
then
  echo "Executable did not exit with code 1 when --port had negative value."
  exit 1
fi

# parameter --port with port zero
"$EXECUTABLE" --board aBcDeFg1234 --port 0
if [ $? -ne 1 ]
then
  echo "Executable did not exit with code 1 when --port had value zero."
  exit 1
fi

# parameter --port with value that is too big
"$EXECUTABLE" --board aBcDeFg1234 --port 34567
if [ $? -ne 1 ]
then
  echo "Executable did not exit with code 1 when --port had out of range value."
  exit 1
fi

# no port number after parameter --port
"$EXECUTABLE" --board aBcDeFg1234 --port
if [ $? -ne 1 ]
then
  echo "Executable did not exit with code 1 when --port had no port number."
  exit 1
fi

# parameter --json given twice
"$EXECUTABLE" --board aBcDeFg1234 --json --json
if [ $? -ne 1 ]
then
  echo "Executable did not exit with code 1 when --json was given twice."
  exit 1
fi

# parameter --move given twice
"$EXECUTABLE" --board aBcDeFg1234 --move --move
if [ $? -ne 1 ]
then
  echo "Executable did not exit with code 1 when --move was given twice."
  exit 1
fi

# parameter --evaluators given twice
"$EXECUTABLE" --board aBcDeFg1234 --evaluators material --evaluators material,check
if [ $? -ne 1 ]
then
  echo "Executable did not exit with code 1 when --evaluators was given twice."
  exit 1
fi

# no evaluator name(s) after parameter --evaluators
"$EXECUTABLE" --board aBcDeFg1234 --evaluators
if [ $? -ne 1 ]
then
  echo "Executable did not exit with code 1 when --evaluators had no evaluator names."
  exit 1
fi

# invalid evaluator name(s) after parameter --evaluators
"$EXECUTABLE" --board aBcDeFg1234 --evaluators foo,bar,baz
if [ $? -ne 1 ]
then
  echo "Executable did not exit with code 1 when --evaluators had invalid evaluator names."
  exit 1
fi

# unknown parameter given
"$EXECUTABLE" --this-is-not-valid-here
if [ $? -ne 1 ]
then
  echo "Executable did not exit with code 1 when an invalid parameter was given."
  exit 1
fi

exit 0
