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

#ifndef SIMPLECHESS_ENGINE_HPP
#define SIMPLECHESS_ENGINE_HPP

#include "../data/Board.hpp"

namespace simplechess
{

class Engine
{
  public:
    /** \brief Provides access to the singleton instance.
     *
     * \return Returns reference to the Engine instance.
     */
    static Engine& get();


    /** Delete copy constructor (singleton). */
    Engine(const Engine& e) = delete;


    /** Avoid implicit move constructor (singleton). */
    Engine(Engine&& e) = delete;


    /** \brief Gets the xboard protocol version.
     *
     * \return Returns the xboard protocol version.
     */
    unsigned int protocolVersion() const;


    /** \brief Sets the xboard protocol version.
     *
     * \param protover  the new protocol version (usually 2)
     */
    void setProtocolVersion(const unsigned int protover);


    /** \brief Gets a reference to the engine's board.
     *
     * \return Returns board reference.
     */
    Board& board();


    /** \brief Gets the side that is controlled by the engine.
     *
     * \return Returns colour of the player that is played by the engine.
     */
    Colour player() const;


    /** \brief Sets the side that is controlled by the engine.
     *
     * \param enginePlayer new colour that is played by the engine
     */
    void setPlayer(const Colour enginePlayer);


    /** \brief Gets the current search depth of the engine.
     *
     * \return Returns the search depth in plys / half moves.
     * \remarks This may currently be one only.
     */
    unsigned int searchDepth() const;


    /** \brief Sets a new search depth for the engine.
     *
     * \param newSearchDepth the new search depth in plys / half moves
     * \remarks The engine may ignore the search depth, if it is larger than
     *          what the engine can currently handle.
     */
    void setSearchDepth(const unsigned int newSearchDepth);
  private:
    unsigned int mProtocolVersion; /**< xboard protocol version */
    Colour mEnginePlayer; /**< colour that is controlled by the engine */
    Board mBoard; /**< current chess board */
    unsigned int mSearchDepth; /**< search depth of the engine in plys */


    /** Default constructor - private due to singleton. */
    Engine();
}; // class

} // namespace

#endif // SIMPLECHESS_ENGINE_HPP
