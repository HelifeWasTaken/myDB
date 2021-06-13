/**
 * File              : Handlers.cpp
 * Author            : Mattis DALLEAU <mattisdalleau@gmail.com>
 * Date              : 13.06.2021
 * Last Modified Date: 13.06.2021
 * Last Modified By  : Mattis DALLEAU <mattisdalleau@gmail.com>
 */
#include <dbhlCommand.hpp>

void dbHL::CommandHandler::HandlerLoaderUsage() {
    std::cerr << "Usage: load file [name] [filename]" << std::endl;
    std::cerr << "Usage: load memory [name] (then press enter and type the json until you type in whole letters EOF)" << std::endl;
}

void dbHL::CommandHandler::HandlerLoader() {
    switch (this->_bufferInputSplitted.size()) {
        case 4:
            if (this->_bufferInputSplitted[1] == "file")
                this->loadCollection(this->_bufferInputSplitted[2], this->_bufferInputSplitted[3]);
            else
                this->HandlerLoaderUsage();
            return;
        case 3:
            if (this->_bufferInputSplitted[1] == "memory")
                std::cout << "Usage of load memory is deprecated please only load file" << std::endl;
            else this->HandlerLoaderUsage();
            return;
        default:
            this->HandlerLoaderUsage();
    }
}

void dbHL::CommandHandler::HandlerDumpUsage() {
    std::cerr << "Usage: dump [collection name]" << std::endl;
    std::cerr << "Usage: dump [collection name] [path]" << std::endl;
}

void dbHL::CommandHandler::HandlerDump() {
    switch (this->_bufferInputSplitted.size()) {
        case 2:
            this->dumpFromCollection(this->_bufferInputSplitted[1]);
            return;
        case 3:
            this->dumpFromCollection(this->_bufferInputSplitted[1], this->_bufferInputSplitted[2]);
            return;
        default:
            this->HandlerDumpUsage();
    }
}

void dbHL::CommandHandler::HandlerCollectionUsage() {
    std::cerr << "Usage: collections" << std::endl;
}

void dbHL::CommandHandler::HandlerCollection() {
    if (this->_bufferInputSplitted.size() != 1)
        return;
    this->collectionsHead();
}

void dbHL::CommandHandler::HandlerCMD() {
    if (this->_bufferInputSplitted[0] == "cd") {
        switch (this->_bufferInputSplitted.size()) {
            case 1:
                if (chdir(std::getenv("HOME")) != 0)
                    std::cerr << "No \"$HOME\" directory found" << std::endl;
                break;
            case 2:
                if (chdir(this->_bufferInputSplitted[1].c_str()) != 0)
                    std::cerr << "No \"" << this->_bufferInputSplitted[1] << "\" directory found" << std::endl;
                break;
            default:
                std::cerr << "Usage: cd [path]" << std::endl; break;
        }
        return;
    }
    if (std::system(this->_bufferInput.c_str()) != 0)
        std::cerr << "Command [" << this->_bufferInput.c_str()
                  << "] not recognized: [load|dump|collections|help|exit]"
                  << std::endl;
}

void dbHL::CommandHandler::HandlerUsage() {
    this->HandlerLoaderUsage();
    this->HandlerCollectionUsage();
    this->HandlerDumpUsage();
}

void dbHL::CommandHandler::HandlerExit() {
    this->_inExitstate = true;
}
