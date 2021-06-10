/**
 * File              : Parser.cpp
 * Author            : Mattis Dalleau <mattis.dalleau@epitech.eu>
 * Date              : 09.06.2021
 * Last Modified Date: 09.06.2021
 * Last Modified By  : Mattis Dalleau <mattis.dalleau@epitech.eu>
 */

#include <JsonParser.hpp>

static const std::string SPACES_TOKENS = " \t\n";
static const std::string TRUE_TOKEN = "true";
static const std::string FALSE_TOKEN = "false";
static const std::string NULL_TOKEN = "null";
static const std::string NUMBER_TOKENS = "0123456789+-";

Json::Parser::Parser() {}

void Json::Parser::unload() {
    if (this->_buffer.empty() == false)
        this->_buffer.clear();
    this->_index = 0;
}

bool Json::Parser::loadFromMemory(std::string buffer) {
    this->unload();
    _buffer = buffer;
    return _buffer.empty() != true;
}

bool Json::Parser::loadFromFile(std::string filename) {
    this->unload();
    std::getline(std::ifstream(filename),this->_buffer, '\0');
    return this->_buffer.empty() != true;
}

Json::Value Json::Parser::parse() {
    Json::Value value;

    if (this->_buffer.empty())
        throw std::runtime_error("You are trying to load a Json from an empty buffer");
    this->parseValue(value);
    return value;
}
