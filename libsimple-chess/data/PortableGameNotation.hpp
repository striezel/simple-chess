/*
 -------------------------------------------------------------------------------
    This file is part of simple-chess.
    Copyright (C) 2017, 2018  Dirk Stolle

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

#ifndef SIMPLE_CHESS_PORTABLE_GAME_NOTATION_HPP
#define SIMPLE_CHESS_PORTABLE_GAME_NOTATION_HPP

#include <map>
#include <string>
#include <unordered_map>
#include <utility>
#include "HalfMove.hpp"
#include "Result.hpp"

namespace simplechess
{

/** Class to hold all information for the Portable Game Notation (PGN) of a
    single game. */
class PortableGameNotation
{
  public:
    /** \brief Default constructor.
     */
    PortableGameNotation();


    /** \brief Gets the name of the tournament or match event.
     *
     * \return name of the tournament or match event
     */
    const std::string& event() const;


    /** \brief Gets the location of the event.
     *
     * \return location of the event
     */
    const std::string& site() const;


    /** \brief Gets the date of the event.
     *
     * \return date of the event
     */
    std::string date() const;


    /** \brief Get the playing round ordinal of the game.
     *
     * \return playing round ordinal of the game
     */
    const std::string& round() const;


    /** \brief Get the player(s) of the white pieces.
     *
     * \return player(s) of the white pieces
     */
    const std::string& white() const;


    /** \brief Get the player(s) of the black pieces.
     *
     * \return player(s) of the black pieces
     */
    const std::string& black() const;


    /** \brief Gets the result of the game, if any.
     *
     * \return result of the game
     */
    const Result& result() const;


    /** \brief Gets the content of a tag.
     *
     * \param tagName   the identifier of the tag
     * \return Returns the content of the tag, if it exists.
     * Returns an empty string, if the tag does not exist.
     */
    std::string tag(const std::string& tagName) const;


    /** \brief Adds a new tag / changes content of existing tag.
     *
     * \param tagName  the name of the tag
     * \param content  content of the tag
     */
    void setTag(const std::string& tagName, const std::string& content);


    /** \brief Deletes an existing tag.
     *
     * \param tagName  the name of the tag to delete
     */
    void clearTag(const std::string& tagName);


    /** \brief Checks whether there is data for the n-th move.
     *
     * \param moveNumber   number of the move (n)
     * \return Returns true, if there is data for the given move.
     */
    bool hasMove(const unsigned int moveNumber) const;


    /** \brief Gets the number of the first move, or zero if there are no moves.
     *
     * \return Returns the positive number of the first move.
     *         Returns zero, if there are no moves yet.
     */
    unsigned int firstMoveNumber() const;


    /** \brief Gets the number of the last move, or zero if there are no moves.
     *
     * \return Returns the positive number of the last move.
     *         Returns zero, if there are no moves yet.
     */
    unsigned int lastMoveNumber() const;


    /** \brief Gets the data for the n-th move.
     *
     * \param moveNumber   number of the move (n)
     * \return Returns a pair of half moves representing the n-th move.
     */
    std::pair<HalfMove, HalfMove> move(const unsigned int moveNumber) const;


    /** \brief Sets the data for a given move.
     *
     * \param moveNumber   number of the move (n)
     * \param whiteMove    white half move
     * \param blackMove    black half move
     */
    void setMove(const unsigned int moveNumber, const HalfMove& whiteMove, const HalfMove& blackMove);


    /** \brief Sets the data for a given move.
     *
     * \param moveNumber   number of the move (n)
     * \param data         pair of half moves: white + black half move
     */
    void setMove(const unsigned int moveNumber, const std::pair<HalfMove, HalfMove>& data);


    /** \brief Gets the game as PGN string.
     *
     * \return Returns the complete PNG notation for the game.
     */
    std::string toString() const;
  private:
      /** \brief Parses a date string by splitting it into its components.
       *
       * \param dateText   the date, e.g. "1992.11.28" or "1993.??.??"
       */
    bool parseDate(const std::string& dateText);

    // tags of the STR (Seven Tag Roster)
    std::string mEvent; /**< name of the tournament or match event */
    std::string mSite; /**< location of the event */
    int mDateYear; /**< date - year component */
    int mDateMonth; /**< date - month component */
    int mDateDay; /**< date - day component */
    std::string mRound; /**< playing round ordinal of the game */
    std::string mWhite; /**< player(s) of the white pieces */
    std::string mBlack; /**< player(s) of the black pieces */
    Result mResult; /**< result of the game */
    // additional tags
    std::unordered_map<std::string, std::string> mOtherTags; /**< other tags */
    // moves
    std::map<unsigned int, std::pair<HalfMove, HalfMove> > mMoves; /**< map of moves; key: move number, value: white move + black move */
}; // class

} // namespace

#endif // SIMPLE_CHESS_PORTABLE_GAME_NOTATION_HPP
