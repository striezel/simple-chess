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

#include <iostream>
#include <string>
#include "../data/PortableGameNotation.hpp"
#include "../pgn/Parser.hpp"
#include "../pgn/Tokenizer.hpp"
#include "../pgn/UnconsumedTokensException.hpp"
#include "../pgn/ParserException.hpp"

const std::string example =
    std::string("[Event \"F/S Return Match\"]\n")
    + "[Site \"Belgrade, Serbia JUG\"]\n"
    + "[Date \"1992.11.04\"]\n"
    + "[Round \"29\"]\n"
    + "[White \"Fischer, Robert J.\"]\n"
    + "[Black \"Spassky, Boris V.\"]\n"
    + "[Result \"1/2-1/2\"]\n"
    + "\n"
    + "1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. O-O Be7 6. Re1 b5 7. Bb3 d6 8. c3\n"
    + "O-O 9. h3 Nb8 10. d4 Nbd7 11. c4 c6 12. cxb5 axb5 13. Nc3 Bb7 14. Bg5 b4 15.\n"
    + "Nb1 h6 16. Bh4 c5 17. dxe5 Nxe4 18. Bxe7 Qxe7 19. exd6 Qf6 20. Nbd2 Nxd6 21.\n"
    + "Nc4 Nxc4 22. Bxc4 Nb6 23. Ne5 Rae8 24. Bxf7+ Rxf7 25. Nxf7 Rxe1+ 26. Qxe1 Kxf7\n"
    + "27. Qe3 Qg5 28. Qxg5 hxg5 29. b3 Ke6 30. a3 Kd6 31. axb4 cxb4 32. Ra5 Nd5 33.\n"
    + "f3 Bc8 34. Kf2 Bf5 35. Ra7 g6 36. Ra6+ Kc5 37. Ke1 Nf4 38. g3 Nxh3 39. Kd2 Kb5\n"
    + "40. Rd6 Kc5 41. Ra6 Nf2 42. g4 Bd3 43. Re6 1/2-1/2\n";

int main(int argc, char** argv)
{
  std::cout << "Hello world!" << std::endl;
  std::vector<simplechess::pgn::Token> tokens;
  bool success = simplechess::pgn::Tokenizer::fromString(example, tokens);
  if (!success)
  {
    std::cout << "Could not tokenize input string!\n";
    return 1;
  }
  simplechess::PortableGameNotation pgn;
  try
  {
    success = simplechess::pgn::Parser::parse(tokens, pgn);
  }
  catch(const simplechess::pgn::UnconsumedTokensException& ex)
  {
    std::cout << "UnconsumedTokensException: " << ex.what() << "\n";
    const auto & tokens = ex.unprocessedTokens();
    std::cout << "First unprocessed token: " << tokens.at(0).text << " of type "
              << (int)tokens.at(0).type << ".\n";
    std::cout << "All remaining tokens:\n";
    for (int i = 0; i < tokens.size(); ++i)
    {
      std::cout << "Type: " << (int)tokens[i].type << " text: \"" << tokens[i].text << "\"\n";
    } //for
    return 2;
  }
  catch(const simplechess::pgn::ParserException& ex)
  {
    std::cout << "ParserException: " << ex.what() << "\n";
    return 2;
  }
  std::cout << "Successfully parsed input data. :)\n";
  std::cout << "\n"
            << "PGN is:\n"
            << pgn.toString() << "\n";
  return 0;
}
