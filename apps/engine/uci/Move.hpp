/*
 -------------------------------------------------------------------------------
    This file is part of simple-chess.
    Copyright (C) 2021  Dirk Stolle

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

#ifndef SIMPLE_CHESS_UCI_MOVE_HPP
#define SIMPLE_CHESS_UCI_MOVE_HPP

#include "../Command.hpp"
#include "../../../libsimple-chess/data/Field.hpp"
#include "../../../libsimple-chess/data/Piece.hpp"

namespace simplechess::uci
{

/** Command for a move made by the user or opposing engine. */
class Move: public Command
{
  public:
    /** \brief Constructor.
     *
     * \param ori  field of origin
     * \param dest destination field
     * \param promo the piece a pawn gets promoted to
     */
    Move(const Field ori, const Field dest, const PieceType promo);


    /** \brief Processes the command, i.e. performs required actions.
     *
     * \return True if command was processed successfully.
     */
    bool process() final;
  private:
    Field origin; /**< field of origin for the move */
    Field destination; /**< field of destination for the move */
    PieceType promoteTo; /**< type of piece that pawns get promoted to */
}; // class

} // namespace

#endif // SIMPLE_CHESS_UCI_MOVE_HPP
