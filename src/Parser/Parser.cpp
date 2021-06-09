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

Json::Parser& Json::Parser::LoadFromMemory(std::string& filename) {
    if (buffer.empty())
        throw "BufferMemory is empty";
    _buffer = buffer;
    return *this;
}

Json::Parser& Json::Parser::LoadFromFile(std::string& filename) {
    std::getline(std::ifstream(filename),this->_buffer, '\0');
    if (this->_buffer.empty())
        throw "File is empty or could not be read properly";
    return *this;
}

Json::Value Json::Parser::parse() {
    Json::Value value;

    if (this->_buffer.empty())
        throw "You are trying to load a Json from an empty buffer";
    this->parseValue(value);
    return value;
}