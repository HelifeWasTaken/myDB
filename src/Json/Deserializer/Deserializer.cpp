/**
 * File              : Deserializer.cpp
 * Author            : Mattis DALLEAU <mattisdalleau@gmail.com>
 * Date              : 10.06.2021
 * Last Modified Date: 10.06.2021
 * Last Modified By  : Mattis DALLEAU <mattisdalleau@gmail.com>
 */
#include <JsonhlDeserializer.hpp>

void jsonhl::Deserializer::loadFromMemory(std::string buffer) {
    this->unload();
    this->loadBuffer(buffer);
    this->_value = this->parse();

}

void jsonhl::Deserializer::loadFromFile(std::string filename) {
    std::string buf;

    this->unload();
    std::getline(std::ifstream(filename), buf, '\0');
    this->loadBuffer(buf);
    this->_value = this->parse();

}

jsonhl::Deserializer::Deserializer() : Parser() {}
