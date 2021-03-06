/*
 -------------------------------------------------------------------------------
    This file is part of simple-chess.
    Copyright (C) 2016, 2017, 2018, 2021  Dirk Stolle

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

#include <array>
#include "Castling.hpp"
#include "Field.hpp"
#include "Piece.hpp"

namespace simplechess
{

/** Class that represents a chess board. */
class Board
{
  public:
    /** \brief Default constructor. */
    Board();


    /** \brief Gets data for a given field on the board.
     *
     * \param f a field on the board
     * \return Returns the piece on the given field.
     */
    const Piece& element(const Field f) const;


    /** \brief Gets the player / colour who is to move next.
     *
     * \return Returns the player / colour who is to move next.
     */
    const Colour& toMove() const;


    /** \brief Gets the field which can be used for en passant capture, if any.
     *
     * \return Returns the field eligible for en passant capture.
     *         Returns Field::none, if no field is eligible.
     */
    const Field& enPassant() const;


    /** \brief Gets the castling information for the board.
     *
     * \return Returns castling information of the board.
     */
    const Castling& castling() const;


    /** \brief Gets the number of halfmoves since the last pawn move or capture.
     *
     * \remarks This counts the number of halfmoves made under the 50 move rule.
     * Once this value is larger than 100, (at least) 50 moves have been made
     * without capturing a piece or moving a pawn. According to the 50 move rule
     * any player can claim a draw in this situation.
     * \return number of halfmoves since last pawn move or capture
     */
    unsigned int halfmovesFifty() const;


    /** \brief Sets a piece on a field on the board.
     *
     * \param field  the field that shall be set
     * \param piece  the piece that shall be set for the field
     * \return Returns true, if the element was set.
     *         Returns false, if it was not set due to invalid value.
     */
    bool setElement(const Field field, const Piece& piece);


    /** \brief Sets the player who currently is to move
     *
     * \param who  player/colour that is to move next (none is not allowed)
     * \return Returns true, if the change was applied.
     *         Returns false, if an invalid value was given and change was not
     *         applied.
     */
    bool setToMove(const Colour who);


    /** \brief Sets the current en passant field.
     *
     * \param ep  the en passant field (use none, if no e.p. is set)
     * \return Returns true, if the new field could be set.
     *         Returns false, if the field was not changed, because the field
     *         is invalid.
     */
    bool setEnPassant(const Field ep);


    /** \brief Sets the current castling information.
     *
     * \param castlingInfo  the new castling information
     */
    void setCastling(const Castling& castlingInfo);


    /** \brief Sets the number of halfmoves since the last pawn move or capture.
     *
     * \remarks This counts the number of halfmoves made under the 50 move rule.
     * \param halfmoves50 number of halfmoves since last pawn move or capture
     */
    void setHalfmovesFifty(const unsigned int halfmoves50);


    /** \brief Determines whether one side is currently in check.
     *
     * \param colour   the colour that is (or is not) in check
     * \return Returns true, if the given colour is in check.
     */
    bool isInCheck(const Colour colour) const;


    /** \brief Updates the internal cache for whether a player is in check.
     */
    void updateCheckCache();


    /** \brief Initializes the board's content with the data from a Forsyth-Edwards notation string.
     *
     * \param FEN  Forsyth-Edwards notation of the board
     * \return Returns true, if initialization was successful.
     *         Returns false otherwise. The board's content is undefined,
     *         if the return value is false.
     */
    bool fromFEN(const std::string& FEN);


    /** \brief Tries to move a piece on the board.
     *
     * \param from       field where the move starts
     * \param to         field where the move ends
     * \param promoteTo  type of piece that a pawn shall be promoted to,
                         if the move allows pawn promotion
     * \param onlyAllowed If set to true, then only moves that are allowed are
                          performed. Otherwise some disallowed moves may be
                          accepted. This is mainly to reduce the number of
                          required rule checks if the move has already been
                          verified before.
     * \return Returns true, if move could be performed.
     *         Returns false, if move was not performed.
     */
    bool move(const Field from, const Field to, PieceType promoteTo, const bool onlyAllowed = true);


    /** \brief Finds the next field where a certain piece is located.
     *
     * \param piece piece for which to search
     * \param start field where search shall start (set to a1, if not sure)
     * \return Returns the first field with the given piece, if it was found.
     *         Returns none, if no matching field was found
     */
    Field findNext(const Piece& piece, Field start) const;
  private:
    std::array<Piece, static_cast<int>(Field::none)> mFields; /**< pieces on fields of the board */
    Colour mToMove; /**< player/colour that is to move next */
    Field  mEnPassant; /**< en passant field, if any */
    Castling mCastling; /**< castling information (i.e. where is castling still allowed) */
    unsigned int mHalfmoves50; /**< number of half moves under the 50 move rule */
    bool mBlackInCheck; /**< whether black player is in check */
    bool mWhiteInCheck; /**< whether white player is in check */
}; // class

} // namespace

#endif // SIMPLE_CHESS_BOARD_HPP
