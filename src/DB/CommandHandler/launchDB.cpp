/**
 * File              : launchDB.cpp
 * Author            : Mattis DALLEAU <mattisdalleau@gmail.com>
 * Date              : 13.06.2021
 * Last Modified Date: 13.06.2021
 * Last Modified By  : Mattis DALLEAU <mattisdalleau@gmail.com>
 */
#include <dbhlCommand.hpp>

void dbHL::CommandHandler::launchDB() {
    std::cout << "> ";
    while (std::getline(std::cin, this->_bufferInput) && this->_inExitstate == false) {
        this->_bufferInputSplitted = boost::split(this->_bufferInputSplitted, this->_bufferInput, boost::is_any_of(", "), boost::token_compress_on);
        ____MCommandHandlerLauncher(this->_bufferInputSplitted[0], *this);
        std::cout << "> ";
    }
    std::cout << "Leaving DB" << std::endl;
}
