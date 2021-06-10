/**
 * File              : Parser.cpp
 * Author            : Mattis Dalleau <mattis.dalleau@epitech.eu>
 * Date              : 09.06.2021
 * Last Modified Date: 09.06.2021
 * Last Modified By  : Mattis Dalleau <mattis.dalleau@epitech.eu>
 */

#include <JsonhlParser.hpp>

jsonhl::Parser::Parser() {}

void jsonhl::Parser::unload() {
    if (this->_buffer.empty() == false)
        this->_buffer.clear();
    this->_index = 0;
}

bool jsonhl::Parser::loadFromMemory(std::string buffer) {
    this->unload();
    _buffer = buffer;
    return _buffer.empty() != true;
}

bool jsonhl::Parser::loadFromFile(std::string filename) {
    this->unload();
    std::getline(std::ifstream(filename),this->_buffer, '\0');
    return this->_buffer.empty() != true;
}

jsonhl::Value jsonhl::Parser::parse() {
    jsonhl::Value value;

    if (this->_buffer.empty())
        throw std::runtime_error("You are trying to load a Json from an empty buffer");
    this->parseValue(value);
    return value;
}
