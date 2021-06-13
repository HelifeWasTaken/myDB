/**
 * File              : CommandLauncherLoad.cpp
 * Author            : Mattis DALLEAU <mattisdalleau@gmail.com>
 * Date              : 13.06.2021
 * Last Modified Date: 13.06.2021
 * Last Modified By  : Mattis DALLEAU <mattisdalleau@gmail.com>
 */

#include <dbhlCommand.hpp>
#include <filesystem>

void dbHL::CommandLauncher::loadCollection(const std::string& name, const std::string& file) {
    jsonhl::Deserializer des;

    if (this->_collections.contains(name) == true)
        throw std::runtime_error("[" + name + "] already exists in the DB");
    des.loadFromFile(file);
    std::cout << "File: [" << file << "] sucessfully loaded as [" << name << "]" << std::endl;
    this->_collections.insert(std::make_pair(name, des));
}

static std::string getFileName(std::string& filePath, char seperator = '/') {
    std::size_t sepPos = filePath.rfind(seperator);
    std::size_t dotPos;
    std::string filePathtmp;

    filePathtmp = sepPos != std::string::npos ? filePath.substr(sepPos + 1, filePath.size()) : filePath;
    dotPos = filePathtmp.rfind('.');
    return dotPos != std::string::npos ? filePathtmp.substr(0, dotPos) : filePathtmp;
}
void dbHL::CommandLauncher::loadDB(std::string& path) {
    for (const auto& dirs : std::filesystem::directory_iterator(path)) {
        std::string fileString = dirs.path().string();
        this->loadCollection(getFileName(fileString), fileString);
    }
}

