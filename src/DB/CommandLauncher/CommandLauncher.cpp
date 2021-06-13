/**
 * File              : CommandLauncher.cpp
 * Author            : Mattis DALLEAU <mattisdalleau@gmail.com>
 * Date              : 13.06.2021
 * Last Modified Date: 13.06.2021
 * Last Modified By  : Mattis DALLEAU <mattisdalleau@gmail.com>
 */
#include <dbhlCommand.hpp>
#include <sys/stat.h>
#include <errno.h>
#include <filesystem>

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

void dbHL::CommandLauncher::collectionsHead() const {
    for (auto it = this->_collections.begin(); it != this->_collections.end(); it++) {
        std::cout << it->first << std::endl;
    }
}

void dbHL::CommandLauncher::loadCollection(const std::string& name, const std::string& file) {
    jsonhl::Deserializer des;

    if (this->_collections.contains(name) == true) {
        throw std::runtime_error("[" + name + "] already exists in the DB");
    }
    des.loadFromFile(file);
    std::cout << "File: [" << file << "] sucessfully loaded as [" << name << "]" << std::endl;
    this->_collections.insert(std::make_pair(name, des));
}

static std::string getFileName(std::string& filePath, char seperator = '/')
{
    std::size_t sepPos = filePath.rfind(seperator);
    std::string filePathtmp;
    if(sepPos != std::string::npos)
        filePathtmp = filePath.substr(sepPos + 1, filePath.size());
    else
        filePathtmp = filePath;
    std::size_t dotPos = filePathtmp.rfind('.');
    if (dotPos != std::string::npos)
        return filePathtmp.substr(0, dotPos);
    return filePathtmp;
}

void dbHL::CommandLauncher::loadDB(std::string& path) {
    struct stat st;

    for (const auto& dirs : std::filesystem::directory_iterator(path)) {
        std::string fileString = dirs.path().string();
        this->loadCollection(getFileName(fileString), fileString);
    }
}

void dbHL::CommandLauncher::saveDB(std::string& path) {
    try {
        const auto& entry = std::filesystem::directory_iterator(path);
        std::cout << "Appending to DB (every collections with the same name will be overwritten)" << std::endl;
    } catch (std::exception& e) {
        if (std::filesystem::create_directory(path) == false)
            throw std::runtime_error(std::string(e.what()) + "->" +
                "std::filesystem::create_directory: Could not create dir");
        this->saveDB(path);
        return;
    }
    if (path.ends_with("/") == false)
        path += "/";
    for (auto it = this->_collections.begin(); it != this->_collections.end(); it++) {
        int indentationLevelBase = 0;
        std::ofstream file(path + it->first + ".json", std::ios::trunc);
        if (file.is_open() == false) {
            std::cerr << "Warning: Could not open: [" << path + it->first + ".json"
                << "] Db will not be complete!" << std::endl;
            continue;
        }
        jsonhl::dump(it->second.getValue(), indentationLevelBase, file);
        std::cout << "Successfully written: [" << path + it->first + ".json"
            << "]" << std::endl;
        file.close();
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
dbHL::CommandLauncher::CommandLauncher()  {}
dbHL::CommandLauncher::~CommandLauncher() {}
