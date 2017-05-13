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

#include "Tokenizer.hpp"
#include <cctype>
#include <fstream>
#include "../util/strings.hpp"

namespace simplechess
{

namespace pgn
{

bool Tokenizer::fromString(const std::string& tokenString, std::vector<Token>& tokens)
{
  tokens.clear();
  if (tokenString.empty())
    return true;

  std::string workString(tokenString);
  while (!workString.empty())
  {
    const bool nextCouldBeHalfMove = !tokens.empty()
        && ((tokens.back().type == TokenType::MoveNumber) || (tokens.back().type == TokenType::HalfMove));

    //left bracket
    if (workString[0] == '[')
    {
      tokens.push_back(Token(TokenType::LeftBracket, "["));
      workString.erase(0, 1);
    }
    //right bracket
    else if (workString[0] == ']')
    {
      tokens.push_back(Token(TokenType::RightBracket, "]"));
      workString.erase(0, 1);
    }
    //string
    else if (workString[0] == '"')
    {
      const auto pos = workString.find('"', 1);
      if (pos == std::string::npos)
      {
        tokens.push_back(Token(TokenType::invalid, workString));
        return false;
      }
      tokens.push_back(Token(TokenType::String, workString.substr(1, pos - 1)));
      workString.erase(0, pos + 1);
    } //else (string)
    //commentary
    else if (workString[0] == '%')
    {
      const auto pos = workString.find('\n', 1);
      if (pos == std::string::npos)
      {
        tokens.push_back(Token(TokenType::invalid, workString));
        return false;
      }
      //just ignore commentary
      workString.erase(0, pos + 1);
    }
    //game ends - wins
    else if ((workString.substr(0, 3) == "1-0") || (workString.substr(0, 3) == "0-1"))
    {
      tokens.push_back(Token(TokenType::GameEnd, workString.substr(0, 3)));
      workString.erase(0, 3);
    }
    //game ends - draw
    else if (workString.substr(0, 7) == "1/2-1/2")
    {
      tokens.push_back(Token(TokenType::GameEnd, workString.substr(0, 7)));
      workString.erase(0, 7);
    }
    //game ends - undecided
    else if (workString[0] == '*')
    {
      tokens.push_back(Token(TokenType::GameEnd, "*"));
      workString.erase(0, 1);
    }
    //move number
    else if (std::isdigit(workString[0]))
    {
      std::string number = std::string(1, workString[0]);
      std::string::size_type idx = 1;
      while ((idx < workString.length()) && std::isdigit(workString[idx]))
      {
        number.append(1, workString[idx]);
        ++idx;
      } //while
      idx = number.length();
      if (idx >= workString.length())
      {
        tokens.push_back(Token(TokenType::invalid, workString));
        return false;
      }
      //dot?
      if (workString[idx] != '.')
      {
        tokens.push_back(Token(TokenType::invalid, workString));
        return false;
      }
      tokens.push_back(Token(TokenType::MoveNumber, number));
      workString.erase(0, idx + 1);
    } //else (move number)
    //half move "..."
    else if ((workString.substr(0, 3) == ".. ") || (workString.substr(0, 3) == "..."))
    {
      tokens.push_back(Token(TokenType::HalfMove, "..."));
      workString.erase(0, 3);
    }
    //identifier
    else if (!nextCouldBeHalfMove && std::isalpha(workString[0]))
    {
      std::string identifier = std::string(1, workString[0]);
      std::string::size_type idx = 1;
      while ((idx < workString.length()) && (std::isalnum(workString[idx])
             || (workString[idx] == '_')))
      {
        identifier.append(1, workString[idx]);
        ++idx;
      } //while
      idx = identifier.length();
      if (idx >= workString.length())
      {
        tokens.push_back(Token(TokenType::invalid, workString));
        return false;
      }
      //space should follow identifier
      if (!std::isspace(workString[idx]))
      {
        tokens.push_back(Token(TokenType::invalid, workString));
        return false;
      }
      tokens.push_back(Token(TokenType::Identifier, identifier));
      workString.erase(0, idx + 1);
    } //else (identifier)
    //half move
    else if (nextCouldBeHalfMove && std::isalpha(workString[0]))
    {
      std::string::size_type pos = workString.find(' ');
      if (pos == std::string::npos)
      {
        if (workString.length() <= 7)
        {
          tokens.push_back(Token(TokenType::HalfMove, workString));
          return true;
        }
        //too long for half move: invalid token
        tokens.push_back(Token(TokenType::invalid, workString));
        return false;
      } //if no space was found
      tokens.push_back(Token(TokenType::HalfMove, workString.substr(0, pos)));
      workString.erase(0, pos);
    }
    //other stuff is invalid token
    else
    {
      tokens.push_back(Token(TokenType::invalid, workString));
      return false;
    }
    //trim any leading whitespace characters
    util::trimLeft(workString);
  } //while
  //finished
  return true;
}

bool Tokenizer::fromFile(const std::string& fileName, std::vector<Token>& tokens)
{
  //reset token list
  tokens.clear();

  std::ifstream stream;
  stream.open(fileName, std::ios_base::binary | std::ios_base::in);
  if (!stream.good() || !stream.is_open())
    return false;

  std::string line;
  while(std::getline(stream, line))
  {
    std::vector<Token> lineTokens;
    const bool success = fromString(line, lineTokens);
    tokens.insert(tokens.end(), lineTokens.begin(), lineTokens.end());
    if (!success)
    {
      stream.close();
      return false;
    }
  } //while
  stream.close();
  return true;
}

} //namespace

} //namespace
