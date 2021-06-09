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

Json::Parser::Parser(std::string& filename, Json::Value& conf) {
    std::getline(std::ifstream(filename), _buffer, '\0');
    if (_buffer.empty())
        throw "File is empty or could not be read properly";
    this->parseValue(conf);
}

Json::Value Json::parseJson(std::string& filename) {
    Json::Value value;

    Json::Parser(filename, value);
    return value;
}