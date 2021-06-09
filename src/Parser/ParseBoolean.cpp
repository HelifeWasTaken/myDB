/**
 * File              : ParseBoolean.cpp
 * Author            : Mattis Dalleau <mattis.dalleau@epitech.eu>
 * Date              : 09.06.2021
 * Last Modified Date: 09.06.2021
 * Last Modified By  : Mattis Dalleau <mattis.dalleau@epitech.eu>
 */
#include <JsonParser.hpp>

bool Json::Parser::parseBoolean(Json::Value& conf) {
    if (this->_buffer.compare(this->_index, TRUE_TOKEN.size(), TRUE_TOKEN) != 0) {
        if (this->_buffer.compare(this->_index, FALSE_TOKEN.size(), FALSE_TOKEN) != 0) {
            return false;
        }
        this->_index += FALSE_TOKEN.size();
        conf = Json::Value(false);
        return true;
    }
    this->_index += TRUE_TOKEN.size();
    conf = Json::Value(true);
    return true;
}
