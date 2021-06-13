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

            void saveDB(std::string& path);
            void loadDB(std::string& path);

            void RenameCollection(std::string& oldName, std::string& newName);

            void DeleteCollection(std::string& collectionName);

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
            void HandlerLoaderDB();
            void HandlerLoaderFile();
            void HandlerLoaderMemory();

            void HandlerDumpUsage();
            void HandlerDump();

            void HandlerCollectionUsage();
            void HandlerCollection();

            void HandlerCMD();

            void HandlerRename();
            void HandlerRenameUsage();

            void HandlerSaveUsage();
            void HandlerSave();

            void HandlerDeleteUsage();
            void HandlerDelete();

            void HandlerExit();

            void HandlerUsage();

        public:
            void launchDB();
    };

    void ____MCommandHandlerLauncherLoaderDB(CommandHandler& self);
    void ____MCommandHandlerLauncherLoaderUsage(CommandHandler& self);
    void ____MCommandHandlerLauncherLoaderFile(CommandHandler& self);
    void ____MCommandHandlerLauncherLoaderMemory(CommandHandler& self);
    void ____MCommandHandlerLauncherDump(CommandHandler& self);
    void ____MCommandHandlerLauncherCollection(CommandHandler& self);
    void ____MCommandHandlerLauncherHelp(CommandHandler& self);
    void ____MCommandHandlerLauncherRename(CommandHandler& self);
    void ____MCommandHandlerLauncherDelete(CommandHandler& self);
    void ____MCommandHandlerLauncherExit(CommandHandler& self);
    void ____MCommandHandlerLauncherSave(CommandHandler& self);

    void ____MCommandHandlerLauncher(std::string& buf, CommandHandler& self);
};
