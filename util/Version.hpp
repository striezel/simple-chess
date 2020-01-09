/*
 -------------------------------------------------------------------------------
    This file is part of simple-chess.
    Copyright (C) 2017, 2018, 2019, 2020  Dirk Stolle

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
 -------------------------------------------------------------------------------
*/

#ifndef SIMPLECHESS_VERSION_HPP
#define SIMPLECHESS_VERSION_HPP

#include <string>

namespace simplechess
{

/** \brief version information */
const std::string version = "version 0.5.4, 2020-01-09";

/** \brief major version number */
const unsigned int versionMajor = 0;

/** \brief minor version number */
const unsigned int versionMinor = 5;

/** \brief patch version number */
const unsigned int versionPatch = 4;

} // namespace

#endif // SIMPLECHESS_VERSION_HPP
