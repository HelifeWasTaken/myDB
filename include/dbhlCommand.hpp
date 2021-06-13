#pragma once

#include <JsonhlDeserializer.hpp>
#include <exception>
#include <list>
#include <unordered_map>
#include <stdexcept>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>

namespace dbHL {

    class CommandLauncher {
        private:
            std::unordered_map<std::string, jsonhl::Deserializer> _collections;

        public:
            void dumpFromCollection(const char *collection, const char *path) const;

            void dumpFromCollection(const char *collection) const;

            void dumpFromCollection(const std::string& collection) const;
            void dumpFromCollection(const std::string& collection, const std::string& path) const;

            void collectionsHead() const;

            void loadCollection(const std::string& name, const std::string& file);

            CommandLauncher();
            ~CommandLauncher();
    };

    class CommandHandler : public CommandLauncher {
        private:
            std::string _bufferInput;
            std::vector<std::string> _bufferInputSplitted;
            bool _inExitstate = false;

        public:
            CommandHandler();
            ~CommandHandler();

        public:
            void HandlerLoaderUsage();
            void HandlerLoader();
            void HandlerDumpUsage();
            void HandlerDump();
            void HandlerCollectionUsage();
            void HandlerCollection();
            void HandlerCMD();
            void HandlerUsage();
            void HandlerExit();

        public:
            void launchDB();
    };

    void ____MCommandHandlerLauncherLoad(CommandHandler& self);
    void ____MCommandHandlerLauncherDump(CommandHandler& self);
    void ____MCommandHandlerLauncherCollection(CommandHandler& self);
    void ____MCommandHandlerLauncherHelp(CommandHandler& self);
    void ____MCommandHandlerLauncherExit(CommandHandler& self);

    void ____MCommandHandlerLauncher(std::string& buf, CommandHandler& self);
};
