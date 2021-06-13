/**
 * File              : CommandLauncherDump.cpp
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
        throw std::runtime_error("[" + std::string(e.what()) + "]: There was no: ["
                + collection + "] or [" + path + "]");
    }
    jsonhl::dump(v);
}

void dbHL::CommandLauncher::dumpFromCollection(const char *collection) const {
    jsonhl::Value v;

    try {
        v = this->_collections.at(collection).getValue();
    } catch (std::exception& e) {
        throw std::runtime_error("[" + std::string(e.what()) + "]: There was no: [" +
                collection + "]");
    }
    jsonhl::dump(v);
}

void dbHL::CommandLauncher::dumpFromCollection(const std::string& collection) const {
    this->dumpFromCollection(collection.c_str());
}
void dbHL::CommandLauncher::dumpFromCollection(const std::string& collection, const std::string& path) const {
    this->dumpFromCollection(collection.c_str(), path.c_str());
}
