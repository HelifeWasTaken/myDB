/**
 * File              : CommandLauncherSave.cpp
 * Author            : Mattis DALLEAU <mattisdalleau@gmail.com>
 * Date              : 13.06.2021
 * Last Modified Date: 13.06.2021
 * Last Modified By  : Mattis DALLEAU <mattisdalleau@gmail.com>
 */

#include <dbhlCommand.hpp>
#include <filesystem>

static void ____MsaveDBLoop(std::unordered_map<std::string, jsonhl::Deserializer>& map, std::string& path) {
    for (auto it = map.begin(); it != map.end(); it++) {
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
    ____MsaveDBLoop(this->_collections, path);
}
