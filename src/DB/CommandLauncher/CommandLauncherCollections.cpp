/**
 * File              : CommandLauncherCollections.cpp
 * Author            : Mattis DALLEAU <mattisdalleau@gmail.com>
 * Date              : 13.06.2021
 * Last Modified Date: 13.06.2021
 * Last Modified By  : Mattis DALLEAU <mattisdalleau@gmail.com>
 */
#include <dbhlCommand.hpp>

void dbHL::CommandLauncher::collectionsHead() const {
    for (auto it = this->_collections.begin(); it != this->_collections.end(); it++) {
        std::cout << it->first << std::endl;
    }
}

void dbHL::CommandLauncher::RenameCollection(std::string& oldName, std::string& newName) {
    const auto& toRename = this->_collections.find(oldName);

    if (toRename == this->_collections.end())
        throw std::runtime_error("[" + oldName + "] Does not exist in the DB");
    if (this->_collections.find(newName) != this->_collections.end())
        throw std::runtime_error("[" + newName + "] Already exist in the DB");
    this->_collections.insert(std::make_pair(newName, toRename->second));
    this->_collections.erase(toRename);
}
