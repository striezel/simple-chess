/*
 -------------------------------------------------------------------------------
    This file is part of simple-chess.
    Copyright (C) 2017, 2021  Dirk Stolle

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

#include "ProtocolVersion.hpp"
#include "../io-utils.hpp"
#include "../Engine.hpp"
#include "../../util/Version.hpp"

namespace simplechess::xboard
{

ProtocolVersion::ProtocolVersion(const unsigned int protoVer)
: protocolVersion(protoVer)
{
}

bool ProtocolVersion::process()
{
  Engine::get().setProtocolVersion(protocolVersion);
  // Send feature commands, if protocol is version 2 or higher.
  if (protocolVersion >= 2)
  {
    sendCommand("feature done=0");
    sendCommand("feature myname=\"simple-chess, " + version + "\"");
    sendCommand("feature ping=1 setboard=1 playother=0 san=0 usermove=1 time=1 sigint=0 sigterm=0 colors=0");
    sendCommand("feature variants=\"normal\"");
    sendCommand("feature done=1");
  }
  return true;
}

} // namespace
