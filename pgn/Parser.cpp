/*
 -------------------------------------------------------------------------------
    This file is part of simple-chess.
    Copyright (C) 2017  Dirk Stolle

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

#include "Parser.hpp"
#include "../util/strings.hpp"

namespace simplechess
{

namespace pgn
{

//parses a tag pair
bool TagPair(const std::vector<Token>& tokens, unsigned int& idx, PortableGameNotation& result)
{
  const auto length = tokens.size();
  //tag pair consists of four tokens
  if (idx + 3 >= length)
    return false;
  if ((tokens[idx].type == TokenType::LeftBracket)
      && (tokens[idx+1].type == TokenType::Identifier)
      && (tokens[idx+2].type == TokenType::String)
      && (tokens[idx+3].type == TokenType::RightBracket))
  {
    result.setTag(tokens[idx+1].text, tokens[idx+2].text);
    idx += 4;
    return true;
  }
  else
    return false;
}

bool FullMove(const std::vector<Token>& tokens, unsigned int& idx, PortableGameNotation& result)
{
  const auto length = tokens.size();
  //full move consists of three tokens
  if (idx + 2 >= length)
    return false;
  if ((tokens[idx].type == TokenType::MoveNumber)
      && (tokens[idx+1].type == TokenType::HalfMove)
      && (tokens[idx+2].type == TokenType::HalfMove))
  {
    int moveNumber = -1;
    if (!util::stringToInt(tokens[idx].text, moveNumber) || (moveNumber < 1))
      return false;
    if (result.hasMove(moveNumber))
      return false;
    HalfMove whiteMove;
    //placeholder move
    if ((tokens[idx+1].text == "..") || (tokens[idx+1].text == "..."))
      whiteMove = HalfMove();
    //"normal" move
    else if (!whiteMove.fromPGN(tokens[idx+1].text))
      return false;
    HalfMove blackMove;
    if (!blackMove.fromPGN(tokens[idx+2].text))
      return false;
    result.setMove(moveNumber, whiteMove, blackMove);
    idx += 3;
    return true;
  }
  else
    return false;
}

bool FinalMove(const std::vector<Token>& tokens, unsigned int& idx, PortableGameNotation& result)
{
  const auto length = tokens.size();
  //full move consists of three tokens
  if (idx + 2 >= length)
    return false;
  if ((tokens[idx].type == TokenType::MoveNumber)
      && (tokens[idx+1].type == TokenType::HalfMove)
      && (tokens[idx+2].type == TokenType::GameEnd))
  {
    int moveNumber = -1;
    if (!util::stringToInt(tokens[idx].text, moveNumber) || (moveNumber < 1))
      return false;
    if (result.hasMove(moveNumber))
      return false;
    HalfMove whiteMove;
    //placeholder move
    if ((tokens[idx+1].text == "..") || (tokens[idx+1].text == "..."))
      whiteMove = HalfMove();
    //"normal" move
    else if (!whiteMove.fromPGN(tokens[idx+1].text))
      return false;
    result.setMove(moveNumber, whiteMove, HalfMove());
    if ((tokens[idx+2].text == "1-0") || (tokens[idx+2].text == "0-1") || (tokens[idx+2].text == "1/2-1/2"))
      result.setTag("Result", tokens[idx+2].text);
    idx += 3;
    return true;
  }
  else
    return false;
}

bool Parser::parse(const std::vector<Token>& tokens, PortableGameNotation& result)
{
  if (tokens.empty())
    return false;
  if (tokens.back().type == TokenType::invalid)
  {
    std::clog << "Invalid token: \"" << tokens.back().text << "\"!" << std::endl;
    return false;
  }
  result = PortableGameNotation();
  unsigned int nextTokenIdx = 0;
  //parse tag pairs
  unsigned int parsedTagPairs = 0;
  while (TagPair(tokens, nextTokenIdx, result))
  {
    ++parsedTagPairs;
  }
  //There should be at least one token pair (or better: 7 or more).
  if (parsedTagPairs == 0)
    return false;

  unsigned int parsedMoves = 0;
  while (FullMove(tokens, nextTokenIdx, result))
  {
    ++parsedMoves;
  }
  if (FinalMove(tokens, nextTokenIdx, result))
  {
    ++parsedMoves;
  }
  //At least one move should have been parsed.
  if (parsedMoves == 0)
    return false;
  //There should be no more tokens.
  if (nextTokenIdx < tokens.size())
    return false;
  //All tokens have been consumed.
  return true;
}

} //namespace

} //namespace
