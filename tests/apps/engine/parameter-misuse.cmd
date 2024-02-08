:: Script to test executable when parameters are used in the wrong way.
::
::  Copyright (C) 2024  Dirk Stolle
::
::  This program is free software: you can redistribute it and/or modify
::  it under the terms of the GNU Lesser General Public License as published by
::  the Free Software Foundation, either version 3 of the License, or
::  (at your option) any later version.
::
::  This program is distributed in the hope that it will be useful,
::  but WITHOUT ANY WARRANTY; without even the implied warranty of
::  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
::  GNU Lesser General Public License for more details.
::
::  You should have received a copy of the GNU Lesser General Public License
::  along with this program.  If not, see <http://www.gnu.org/licenses/>.

@echo off

:: 1st parameter = executable path
if "%1" EQU "" (
  echo First parameter must be executable file!
  exit /B 1
)

SET EXECUTABLE=%1

:: parameter --evaluators given twice
"%EXECUTABLE%" --evaluators material --evaluators material,check
if %ERRORLEVEL% NEQ 1 (
  echo Executable did not exit with code 1 when --evaluators was given twice.
  exit /B 1
)

:: no evaluator name(s) after parameter --evaluators
"%EXECUTABLE%" --evaluators
if %ERRORLEVEL% NEQ 1 (
  echo Executable did not exit with code 1 when --evaluators had no evaluator names.
  exit /B 1
)

:: invalid evaluator name(s) after parameter --evaluators
"%EXECUTABLE%" --evaluators foo,bar,baz
if %ERRORLEVEL% NEQ 1 (
  echo Executable did not exit with code 1 when --evaluators had invalid evaluator names.
  exit /B 1
)

:: unknown parameter
"%EXECUTABLE%" --this-is-not-supported
if %ERRORLEVEL% NEQ 1 (
  echo Executable did not exit with code 1 when an unknown parameter was given.
  exit /B 1
)

exit 0
