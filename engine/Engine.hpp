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

#ifndef SIMPLECHESS_ENGINE_HPP
#define SIMPLECHESS_ENGINE_HPP

#include <atomic>
#include <deque>
#include <memory>

#include "../data/Board.hpp"
#include "../evaluation/CompoundEvaluator.hpp"
#include "time/Timing.hpp"
#include "xboard/Command.hpp"

namespace simplechess
{

/** Central class for the XBoard-compatible chess engine of simple-chess. */
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


    /** \brief Checks whether the engine has received the quit command.
     *
     * \return Returns true, if the quit command has been received.
     */
    bool quitRequested() const;


    /** \brief Request the termination of command processing and any further
     *         engine activity to the earliest possible convenient moment.
     * \remarks Only call this method if you want to shutdown the engine.
     */
    void terminate();


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


    /** \brief Gets the current evaluator for the engine (usually compound).
     *
     * \return current evaluator
     */
    const Evaluator& evaluator() const noexcept;


    /** \brief Sets the current evaluator for the engine.
     *
     * \param eval  the new evaluator for the engine
     * \return true, if evaluator was accepted; false otherwise
     */
    bool setEvaluator(CompoundEvaluator&& eval);


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


    /** \brief Checks whether the engine is currently in force mode.
     *
     * \return Returns true, if engine is in force mode. Returns false otherwise.
     */
    bool forceMode() const;


    /** \brief Sets whether force mode is on or not.
     *
     * \param newForceMode true to set force mode, false to leave force mode
     */
    void setForceMode(const bool newForceMode);


    /** \brief Gets the timing control of the engine.
     *
     * \return timing control instance
     */
    Timing& timing();


    /** \brief Adds another command to the command queue.
     *
     * \param com  the command that shall be added
     */
    void addCommand(std::unique_ptr<Command>&& com);


    /** \brief Gets a constant reference to the current command queue.
     *
     * \return Returns a constant reference to command queue.
     */
    const std::deque<std::unique_ptr<Command> >& queue() const;


    /** \brief Processes all remaining commands in the queue.
     *
     * \return Returns the number of processed commands.
     */
    int processQueue();


    /** \brief Ask the engine to think about and eventually perform the next
     *         move for the current player.
     */
    void move();
  private:
    std::atomic<bool> mQuit; /**< quit flag - it true, termination has been requested */
    unsigned int mProtocolVersion; /**< xboard protocol version */
    Colour mEnginePlayer; /**< colour that is controlled by the engine */
    Board mBoard; /**< current chess board */
    CompoundEvaluator evaluators; /**< evaluators that are used by the engine */
    unsigned int mSearchDepth; /**< search depth of the engine in plys */
    bool mForceMode; /**< whether the engine is in force mode */
    Timing mTiming; /**< time controls */
    std::deque<std::unique_ptr<Command> > mQueue; /**< command queue */


    /** Default constructor - private due to singleton. */
    Engine();
}; // class

} // namespace

#endif // SIMPLECHESS_ENGINE_HPP
