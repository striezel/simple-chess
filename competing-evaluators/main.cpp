/*
 -------------------------------------------------------------------------------
    This file is part of simple-chess.
    Copyright (C) 2020  Dirk Stolle

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
#if defined(__linux__) || defined(linux)
#include <csignal>
#elif defined(_WIN32)
#include <Windows.h>
#endif
#include "../util/GitInfos.hpp"
#include "../util/ReturnCodes.hpp"
#include "../util/Version.hpp"
#include "competing.hpp"
#include "CompetitionData.hpp"

void showVersion()
{
  simplechess::GitInfos info;
  std::cout << "simple-chess-competing-evaluators, " << simplechess::version << "\n"
            << "\n"
            << "Version control commit: " << info.commit() << "\n"
            << "Version control date:   " << info.date() << std::endl;
}

void showHelp()
{
  std::cout << "simple-chess-competing-evaluators [OPTIONS]\n"
            << "\n"
            << "options:\n"
            << "  -? | --help     - shows this help message and exits\n"
            << "  -v | --version  - shows version information and exits\n";
}

simplechess::CompetitionData compData(simplechess::Competition::allEvaluators);

#if defined(__linux__) || defined(linux)
/** \brief signal handling function for Linux systems
 *
 * \param sig   the signal number (e.g. 15 for SIGTERM)
 * \remarks This function will not return, because it calls std::exit() at
 *          the end. std::exit() never returns.
 */
void linux_signal_handler(int sig)
{
  std::clog << "INFO: Caught signal ";
  switch (sig)
  {
    case SIGTERM:
         std::clog << "SIGTERM";
         break;
    case SIGINT:
         std::clog << "SIGINT";
         break;
    case SIGUSR1:
         std::clog << "SIGUSR1";
         break;
    case SIGUSR2:
         std::clog << "SIGUSR2";
         break;
    default:
        std::clog << sig;
        break;
  } //switch
  std::clog << "!" << std::endl;
  // Show the summary, i.e. competition results we have so far.
  compData.show();
  std::clog << "Terminating program early due to caught signal." << std::endl;
  std::exit(simplechess::rcProgramTerminationBySignal);
}
#elif defined(_WIN32)
/** \brief signal handling function for Windows systems
 *
 * \param ctrlSignal   the received control signal
 * \return Returns false, if signal was not handled.
 *         Hypothetically returns true, if signal was handled, but in that
 *         case std::exit() steps in to terminate the program.
 * \remarks This function will never return true, because it calls std::exit()
 *          at the end, when a signal is handled. std::exit() never returns.
 */
BOOL windows_signal_handler(DWORD ctrlSignal)
{
  switch (ctrlSignal)
  {
    case CTRL_C_EVENT:
         std::clog << "INFO: Received Ctrl+C!";
         // Show the summary, i.e. competition results we have so far.
         compData.show();
         std::clog << "Terminating program early due to caught signal." << std::endl;
         std::exit(simplechess::rcProgramTerminationBySignal);
         return TRUE; // bogus
         break;
  }
  return FALSE;
}
#endif

int main(int argc, char** argv)
{
  if ((argc > 1) && (argv != nullptr))
  {
    for (int i = 1; i < argc; ++i)
    {
      if (argv[i] == nullptr)
      {
        std::cerr << "Error: Parameter at index " << i << " is null pointer!\n";
        return 1;
      }
      const std::string param(argv[i]);
      if ((param == "-v") || (param == "--version"))
      {
        showVersion();
        return 0;
      } // if version
      else if ((param == "-?") || (param == "--help") || (param == "/?"))
      {
        showHelp();
        return 0;
      } // if help
      // Should never happen.
      else
      {
        std::cerr << "Error: Unknown parameter " << param << "!\n"
                  << "Use --help to show available parameters." << std::endl;
        return simplechess::rcInvalidParameter;
      }
    } // for i
  } // if arguments are there

  // install signal handlers
  #if defined(__linux__) || defined(linux)
  struct sigaction sa;

  sa.sa_handler = linux_signal_handler;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = 0;
  // Install one for SIGINT ...
  if (sigaction(SIGINT, &sa, nullptr) != 0)
  {
    std::clog << "Error: Could not set signal handling function for SIGINT!"
              << std::endl;
    return simplechess::rcSignalHandlerError;
  }
  // ... and one for SIGTERM.
  if (sigaction(SIGTERM, &sa, nullptr) != 0)
  {
    std::clog << "Error: Could not set signal handling function for SIGTERM!"
              << std::endl;
    return simplechess::rcSignalHandlerError;
  }
  // ... and one for SIGUSR1, ...
  if (sigaction(SIGUSR1, &sa, nullptr) != 0)
  {
    std::clog << "Error: Could not set signal handling function for SIGUSR1!"
              << std::endl;
    return simplechess::rcSignalHandlerError;
  }
  // ... and one for SIGUSR2.
  if (sigaction(SIGUSR2, &sa, nullptr) != 0)
  {
    std::clog << "Error: Could not set signal handling function for SIGUSR2!"
              << std::endl;
    return simplechess::rcSignalHandlerError;
  }
  #elif defined(_WIN32)
  if (SetConsoleCtrlHandler((PHANDLER_ROUTINE) windows_signal_handler, TRUE) == 0)
  {
    std::clog << "Error: Could not set signal handling function for Ctrl+C!"
              << std::endl;
    return simplechess::rcSignalHandlerError;
  } //if
  #else
    #error Unknown operating system! No known signal handling facility.
  #endif // defined

  std::cout << "Pairing all evaluator combinations, this will take quite some time..."
            << std::endl;
  if (compData.compete())
  {
    compData.show();
  }
  else
  {
    std::cout << "Failed to let all evaluators compete!" << std::endl;
  }
  std::cout << "Finished." << std::endl;
  return 0;
}
