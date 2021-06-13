/**
 * File              : Handlers.cpp
 * Author            : Mattis DALLEAU <mattisdalleau@gmail.com>
 * Date              : 13.06.2021
 * Last Modified Date: 13.06.2021
 * Last Modified By  : Mattis DALLEAU <mattisdalleau@gmail.com>
 */
#include <dbhlCommand.hpp>

static const char *ALL_HANDLER_COMMANDS_POSSIBLE =
  "[loadFile|loadMemory|loadDB|dump|"
  "rename|collections|delete|help|exit]";


void dbHL::CommandHandler::HandlerLoaderUsage() {
    std::cerr << "Usage: loadFile [name] [filename]" << std::endl;
    std::cerr << "Usage: loadMemory [name] (then press enter and type the json until you type in whole letters EOF)" << std::endl;
    std::cerr << "Usage: loadDB [DirName]" << std::endl;
}

void dbHL::CommandHandler::HandlerDumpUsage() {
    std::cerr << "Usage: dump [collection name]" << std::endl;
    std::cerr << "Usage: dump [collection name] [path]" << std::endl;
}

void dbHL::CommandHandler::HandlerCollectionUsage() {
    std::cerr << "Usage: collections" << std::endl;
}

void dbHL::CommandHandler::HandlerRenameUsage() {
    std::cerr << "Usage: rename [collectionName] [newName]" << std::endl;
}

void dbHL::CommandHandler::HandlerSaveUsage() {
    std::cerr << "Usage: save [filepath]" << std::endl;
}

void dbHL::CommandHandler::HandlerDeleteUsage() {
    std::cerr << "Usage: delete [collectionName]" << std::endl;
}

void dbHL::CommandHandler::HandlerUsage() {
    this->HandlerLoaderUsage();
    this->HandlerCollectionUsage();
    this->HandlerDumpUsage();
    this->HandlerSaveUsage();
    this->HandlerRenameUsage();
    this->HandlerDeleteUsage();
}

void dbHL::CommandHandler::HandlerLoaderDB() {
    if (this->_bufferInputSplitted.size() == 2)
        this->loadDB(this->_bufferInputSplitted[1]);
    else
        this->HandlerLoaderUsage();
}

void dbHL::CommandHandler::HandlerLoaderFile() {
    if (this->_bufferInputSplitted.size() == 3)
        this->loadCollection(this->_bufferInputSplitted[1], this->_bufferInputSplitted[2]);
    else
        this->HandlerLoaderUsage();
}

void dbHL::CommandHandler::HandlerLoaderMemory() {
    if (this->_bufferInputSplitted.size() == 3)
        std::cout << "Usage of load memory is deprecated please only load file" << std::endl;
    else
        this->HandlerLoaderUsage();
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


void dbHL::CommandHandler::HandlerCollection() {
    if (this->_bufferInputSplitted.size() != 1)
        this->HandlerCollectionUsage();
    else
        this->collectionsHead();
}

static void ____MHandlerCMDBuiltinCD(std::vector<std::string>& _bufferInputSplitted) {
    switch (_bufferInputSplitted.size()) {
        case 1:
            if (chdir(std::getenv("HOME")) != 0)
                std::cerr << "No \"$HOME\" directory found" << std::endl;
            break;
        case 2:
            if (chdir(_bufferInputSplitted[1].c_str()) != 0)
                std::cerr << "No \"" << _bufferInputSplitted[1] << "\" directory found" << std::endl;
            break;
        default:
            std::cerr << "Usage: cd [path]" << std::endl; break;
    }
}

void dbHL::CommandHandler::HandlerCMD() {
    if (this->_bufferInputSplitted[0] == "cd") {
        ____MHandlerCMDBuiltinCD(this->_bufferInputSplitted);
    } else if (std::system(this->_bufferInput.c_str()) != 0)
        std::cerr << "Command ["
            << this->_bufferInput.c_str() << "] not recognized:"
            << ALL_HANDLER_COMMANDS_POSSIBLE << std::endl;
}

void dbHL::CommandHandler::HandlerSave() {
    if (this->_bufferInputSplitted.size() == 2)
        this->saveDB(this->_bufferInputSplitted[1]);
    else
        this->HandlerSaveUsage();
}

void dbHL::CommandHandler::HandlerExit() {
    this->_inExitstate = true;
}

void dbHL::CommandHandler::HandlerRename() {
    if (this->_bufferInputSplitted.size() != 3) {
        this->HandlerRenameUsage();
        return;
    }
    try {
        this->RenameCollection(this->_bufferInputSplitted[1], this->_bufferInputSplitted[2]);
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

void dbHL::CommandHandler::HandlerDelete() {
    if (this->_bufferInputSplitted.size() != 2)
        this->HandlerDeleteUsage();
    else
        this->DeleteCollection(this->_bufferInputSplitted[1]);
}
