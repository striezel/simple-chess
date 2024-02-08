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

# parameter white given twice
"$EXECUTABLE" white white
if [ $? -ne 1 ]
then
  echo "Executable did not exit with code 1 when white was given twice."
  exit 1
fi

# parameter black given twice
"$EXECUTABLE" black black
if [ $? -ne 1 ]
then
  echo "Executable did not exit with code 1 when black was given twice."
  exit 1
fi

# parameter --show-labels given twice
"$EXECUTABLE" --show-labels --show-labels
if [ $? -ne 1 ]
then
  echo "Executable did not exit with code 1 when --show-labels was given twice."
  exit 1
fi

# parameter --hide-labels given twice
"$EXECUTABLE" --hide-labels --hide-labels
if [ $? -ne 1 ]
then
  echo "Executable did not exit with code 1 when --hide-labels was given twice."
  exit 1
fi

# parameter --letters given twice
"$EXECUTABLE" --letters --letters
if [ $? -ne 1 ]
then
  echo "Executable did not exit with code 1 when --letters was given twice."
  exit 1
fi

# parameter --symbols given twice
"$EXECUTABLE" --symbols --symbols
if [ $? -ne 1 ]
then
  echo "Executable did not exit with code 1 when --symbols was given twice."
  exit 1
fi

# parameter --evaluators given twice
"$EXECUTABLE" --evaluators material --evaluators material,check
if [ $? -ne 1 ]
then
  echo "Executable did not exit with code 1 when --evaluators was given twice."
  exit 1
fi

# no evaluator name(s) after parameter --evaluators
"$EXECUTABLE" --evaluators
if [ $? -ne 1 ]
then
  echo "Executable did not exit with code 1 when --evaluators had no evaluator names."
  exit 1
fi

# invalid evaluator name(s) after parameter --evaluators
"$EXECUTABLE" --evaluators foo,bar,baz
if [ $? -ne 1 ]
then
  echo "Executable did not exit with code 1 when --evaluators had invalid evaluator names."
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
