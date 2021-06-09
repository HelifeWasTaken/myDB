/**
 * File              : ParseUtil.cpp
 * Author            : Mattis Dalleau <mattis.dalleau@epitech.eu>
 * Date              : 09.06.2021
 * Last Modified Date: 09.06.2021
 * Last Modified By  : Mattis Dalleau <mattis.dalleau@epitech.eu>
 */
#include <JsonParser.hpp>

bool Json::Parser::isToken(char const& c, const std::string& tokens) const {
    return tokens.find(c) != std::string::npos;
}
void Json::Parser::skipSpaces(void) {
    for (; this->_index < this->_buffer.size() &&
        this->isToken(this->_buffer.at(this->_index), this->SPACES_TOKENS); this->_index++);
}
