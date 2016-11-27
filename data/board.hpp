/*
 -------------------------------------------------------------------------------
    This file is part of simple-chess.
    Copyright (C) 2016  Dirk Stolle

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

#ifndef SIMPLE_CHESS_BOARD_HPP
#define SIMPLE_CHESS_BOARD_HPP

#include <map>
#include "castling.hpp"
#include "field.hpp"
#include "piece.hpp"

namespace simplechess
{

/* class that represents a chess board */
class Board
{
  public:
    /* default constructor */
    Board();

    /* gets data for a given field on the board */
    const Piece& element(const Field f) const;

    /* gets the player / colour who is to move next */
    const Colour& toMove() const;

    /* gets the field which can be used for en passant capture, if any */
    const Field& enPassant() const;

    /* castling information for the board */
    const Castling& castling() const;


    /** \brief determines whether one side is currently in check
     *
     * \param colour   the colour that is (or is not) in check
     * \return Returns true, if the given colour is in check;
     */
    bool isInCheck(const Colour colour) const;


    /** \brief initializes the board's content with the data from a Forsyth-Edwards notation string
     *
     * \param FEN  Forsyth-Edwards notation of the board
     * \return Returns true, if initialization was successful.
     *         Returns false otherwise. The board's content is undefined,
     *         if the return value is false.
     */
    bool fromFEN(const std::string& FEN);


    /** \brief tries to move a piece on the board
     *
     * \param from       field where the move starts
     * \param to         field where the move ends
     * \param promoteTo  type of piece that a pawn shall be promoted to,
                         if the move allows pawn promotion
     * \return Returns true, if move could be performed.
     * Returns false, if move was not performed.
     */
    bool move(const Field from, const Field to, PieceType promoteTo);
  private:
    std::map<Field, Piece> m_Fields; /**< pieces on fields of the board */
    Colour m_toMove; /**< player/colour that is to move next */
    Field  m_enPassant; /**< en passant field, if any */
    Castling m_castling; /**< castling information (i.e. where is castling still allowed) */
    bool m_blackInCheck; /**< whether black player is in check */
    bool m_whiteInCheck; /**< whether white player is in check */
}; //class

} //namespace

#endif // SIMPLE_CHESS_BOARD_HPP
