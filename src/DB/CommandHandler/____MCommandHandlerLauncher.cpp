/**
 * File              : ____MCommandHandlerLauncher.cpp
 * Author            : Mattis DALLEAU <mattisdalleau@gmail.com>
 * Date              : 13.06.2021
 * Last Modified Date: 13.06.2021
 * Last Modified By  : Mattis DALLEAU <mattisdalleau@gmail.com>
 */

#include <dbhlCommand.hpp>

namespace dbHL {
    void ____MCommandHandlerLauncherLoaderDB(CommandHandler& self) {
        self.HandlerLoaderDB();
    }
    void ____MCommandHandlerLauncherLoaderMemory(CommandHandler& self) {
        self.HandlerLoaderMemory();
    }
    void ____MCommandHandlerLauncherLoaderFile(CommandHandler& self) {
        self.HandlerLoaderFile();
    }
    void ____MCommandHandlerLauncherDump(CommandHandler& self) {
        self.HandlerDump();
    }
    void ____MCommandHandlerLauncherCollection(CommandHandler& self) {
        self.HandlerCollection();
    }
    void ____MCommandHandlerLauncherHelp(CommandHandler& self) {
        self.HandlerUsage();
    }
    void ____MCommandHandlerLauncherExit(CommandHandler& self) {
        self.HandlerExit();
    }
    void ____MCommandHandlerLauncherSave(CommandHandler& self) {
        self.HandlerSave();
    }
    void ____MCommandHandlerLauncherRename(CommandHandler& self) {
        self.HandlerRename();
    }

    void ____MCommandHandlerLauncher(std::string& buf, CommandHandler& self) {
        static const std::map<std::string, std::function<void (CommandHandler&)>> launchers = {
            { "loadFile", ____MCommandHandlerLauncherLoaderFile },
            { "loadMemory", ____MCommandHandlerLauncherLoaderMemory },
            { "loadDB", ____MCommandHandlerLauncherLoaderDB },
            { "dump", ____MCommandHandlerLauncherDump },
            { "collections", ____MCommandHandlerLauncherCollection },
            { "rename", ____MCommandHandlerLauncherRename },
            { "help", ____MCommandHandlerLauncherHelp },
            { "exit", ____MCommandHandlerLauncherExit },
            { "save", ____MCommandHandlerLauncherSave }
        };

        try {
            if (launchers.contains(buf) == false) {
                self.HandlerCMD();
                return;
            }
            launchers.at(buf)(self);
        } catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }
};
