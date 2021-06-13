/**
 * File              : CommandLauncher.cpp
 * Author            : Mattis DALLEAU <mattisdalleau@gmail.com>
 * Date              : 13.06.2021
 * Last Modified Date: 13.06.2021
 * Last Modified By  : Mattis DALLEAU <mattisdalleau@gmail.com>
 */
#include <dbhlCommand.hpp>

void dbHL::CommandLauncher::dumpFromCollection(const char *collection, const char *path) const {
    jsonhl::Value v;

    try {
        v = this->_collections.at(collection).get(path);
    } catch (std::exception& e) {
        std::cerr << "[" << e.what() << "]: There was no: ["
            << collection << "] or [" << path << "]" << std::endl;
        return;
    }
    jsonhl::dump(v);
}

void dbHL::CommandLauncher::dumpFromCollection(const char *collection) const {
    jsonhl::Value v;

    try {
        v = this->_collections.at(collection).getValue();
    } catch (std::exception& e) {
        std::cerr << "[" << e.what() << "]: There was no: [" << collection << "]" << std::endl;
        return;
    }
    jsonhl::dump(v);
}

void dbHL::CommandLauncher::dumpFromCollection(const std::string& collection) const {
    this->dumpFromCollection(collection.c_str());
}
void dbHL::CommandLauncher::dumpFromCollection(const std::string& collection, const std::string& path) const {
    this->dumpFromCollection(collection.c_str(), path.c_str());
}

void dbHL::CommandLauncher::collectionsHead() const {
    for (auto it = this->_collections.begin(); it != this->_collections.end(); it++) {
        std::cout << it->first << std::endl;
    }
}

void dbHL::CommandLauncher::loadCollection(const std::string& name, const std::string& file) {
    jsonhl::Deserializer des;

    if (this->_collections.contains(name) == true) {
        std::cerr << "[" << name << "] already exists in the DB" << std::endl;
        return;
    }
    try {
        des.loadFromFile(file);
    } catch (std::exception& e) {
        std::cerr << "[" << e.what() << "]" << std::endl;
        return;
    }
    std::cout << "File: [" << file << "] sucessfully loaded as [" << name << "]" << std::endl;
    this->_collections.insert(std::make_pair(name, des));
}

dbHL::CommandLauncher::CommandLauncher() {}
dbHL::CommandLauncher::~CommandLauncher() {}
