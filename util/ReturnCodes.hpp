/*
 -------------------------------------------------------------------------------
    This file is part of simple-chess.
    Copyright (C) 2017, 2018, 2019  Dirk Stolle

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

#ifndef SIMPLECHESS_RETURNCODES_HPP
#define SIMPLECHESS_RETURNCODES_HPP

namespace simplechess
{

// Common return codes / exit codes that are used by simple-chess programs.

const int rcInvalidParameter = 1;
const int rcTokenizationError = 2;
const int rcParserError = 3;
const int rcDataImplausible = 4;
const int rcBoardInitializationFailure = 5;
const int rcMoveNotPossible = 6;
#ifndef NO_METEOR_CHESS
const int rcMongoDbError = 7;
#endif // NO_METEOR_CHESS
const int rcEngineResigns = 8;
const int rcEngineClaimsDraw = 9; // ... under 50 move rule
const int rcUnknown = 10;

} // namespace

#endif // SIMPLECHESS_RETURNCODES_HPP
