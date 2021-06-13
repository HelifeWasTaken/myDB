/**
 * File              : ____MCommandHandlerLauncher.cpp
 * Author            : Mattis DALLEAU <mattisdalleau@gmail.com>
 * Date              : 13.06.2021
 * Last Modified Date: 13.06.2021
 * Last Modified By  : Mattis DALLEAU <mattisdalleau@gmail.com>
 */

#include <dbhlCommand.hpp>

namespace dbHL {
    void ____MCommandHandlerLauncherLoad(CommandHandler& self) {
        self.HandlerLoader();
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

    void ____MCommandHandlerLauncher(std::string& buf, CommandHandler& self) {
        static const std::map<std::string, std::function<void (CommandHandler&)>> launchers = {
            { "load", ____MCommandHandlerLauncherLoad },
            { "dump", ____MCommandHandlerLauncherDump },
            { "collections", ____MCommandHandlerLauncherCollection },
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
