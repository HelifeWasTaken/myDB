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
            void dumpFromCollection(const char *collection, const char *path) const {
                jsonhl::Value v;

                try {
                    v = this->_collections.at(collection).get(path);
                } catch (std::exception& e) {
                    std::cerr << "[" << e.what() << "]: There was no: [" << collection << "]" << "or [" << path << "]" << std::endl;
                    return;
                }
                jsonhl::dump(v);
            }

            void dumpFromCollection(const char *collection) const {
                jsonhl::Value v;

                try {
                    v = this->_collections.at(collection).getValue();
                } catch (std::exception& e) {
                    std::cerr << "[" << e.what() << "]: There was no: [" << collection << "]" << std::endl;
                    return;
                }
                jsonhl::dump(v);
            }

            void dumpFromCollection(const std::string& collection) const { this->dumpFromCollection(collection.c_str()); }
            void dumpFromCollection(const std::string& collection, const std::string& path) const { this->dumpFromCollection(collection.c_str(), path.c_str()); }

            void collectionsHead() const {
                for (auto it = this->_collections.begin(); it != this->_collections.end(); it++) {
                    std::cout << it->first << std::endl;
                }
            }

            void loadCollection(const std::string& name, const std::string& file) {
                jsonhl::Deserializer des;

                std::cout << "File: " << file << std::endl;
                try {
                    des.loadFromFile(file);
                } catch (std::exception& e) {
                    std::cerr << "[" << e.what() << "]" << std::endl;
                    return;
                }
                this->_collections.insert(std::make_pair(name, des));
            }

            CommandLauncher() {}
            ~CommandLauncher() {}
    };

    class CommandHandler : public CommandLauncher {
        private:
            std::string _bufferInput;
            std::vector<std::string> _bufferInputSplitted;


        public:
            CommandHandler() {}
            ~CommandHandler() {}

            void HandlerLoaderUsage() {
                std::cout << "Usage: load file [name] [filename]" << std::endl;
                std::cout << "Usage: load memory [name] (then press enter and type the json until you type in whole letters EOF)" << std::endl;
            }

            void HandlerLoader() {
                switch (this->_bufferInputSplitted.size()) {
                    case 4:
                        if (this->_bufferInputSplitted[1] == "file")
                            this->loadCollection(this->_bufferInputSplitted[2], this->_bufferInputSplitted[3]);
                        else this->HandlerLoaderUsage();
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

            void HandlerDumpUsage() {
                std::cout << "Usage: dump [collection name]" << std::endl;
                std::cout << "Usage: dump [collection name] [path]" << std::endl;
            }

            void HandlerDump() {
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

            void HandlerCollectionUsage() {
                std::cout << "Usage: collections" << std::endl;
            }

            void HandlerCollection() {
                if (this->_bufferInputSplitted.size() != 1)
                    return;
                this->collectionsHead();
            }

            bool HandlerCMD() {
                if (this->_bufferInputSplitted[0] == "cd") {
                    try {
                        switch (this->_bufferInputSplitted.size()) {
                            case 1: chdir(std::getenv("HOME")); break;
                            case 2: chdir(this->_bufferInputSplitted[1].c_str()); break;
                            default: std::cout << "Usage: cd [path]" << std::endl;
                        }
                    } catch (std::exception& e) {
                        std::cerr << e.what() << std::endl;
                    }
                    return true;
                }
                return std::system(this->_bufferInput.c_str()) == 0;
            }

        public:
            void launchDB() {
                std::cout << "> ";
                while (std::getline(std::cin, this->_bufferInput)) {
                    this->_bufferInputSplitted = boost::split(this->_bufferInputSplitted, this->_bufferInput, boost::is_any_of(", "), boost::token_compress_on);
                    if (this->_bufferInputSplitted.size() == 0)
                        continue;
                    if (this->_bufferInputSplitted[0] == "load") this->HandlerLoader();
                    else if (this->_bufferInputSplitted[0] == "dump") this->HandlerDump();
                    else if (this->_bufferInputSplitted[0] == "collections") this->HandlerCollection();
                    else if (this->_bufferInputSplitted[0] == "help") {
                        this->HandlerLoaderUsage();
                        this->HandlerCollectionUsage();
                        this->HandlerDumpUsage();
                    } else if (this->_bufferInputSplitted[0] == "exit") break;
                    else if (this->HandlerCMD() == false) std::cout << "Command not recognized: [load|dump|collections|help|exit]" << std::endl;
                    std::cout << "> ";
                }
                std::cout << "Leaving DB" << std::endl;
            }
    };
};
