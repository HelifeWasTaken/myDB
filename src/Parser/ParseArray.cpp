/**
 * File              : ParseArray.cpp
 * Author            : Mattis Dalleau <mattis.dalleau@epitech.eu>
 * Date              : 09.06.2021
 * Last Modified Date: 09.06.2021
 * Last Modified By  : Mattis Dalleau <mattis.dalleau@epitech.eu>
 */
#include <JsonParser.hpp>

void Json::Parser::____MJsonReadArray(Json::Value& conf, Json::Value::Array& arr) {
    Json::Value tmp;

    while (this->_buffer.at(this->_index)) {
        this->skipSpaces();
        if (this->_buffer.at(this->_index) == ']') {
            this->_index++;
            conf = Json::Value(arr);
            return;
        }
        if (this->_buffer.at(this->_index) != ',')
            throw "Expected ',' after value [array]";
        this->_index++;
        this->parseValue(tmp);
        arr.push_back(tmp);
        tmp = Json::Value();
    }
    throw "Expected ']' at the end of the array";
}

bool Json::Parser::parseArray(Json::Value& conf) {
    Json::Value tmp;
    Json::Value::Array arr;

    if (this->_buffer.at(this->_index) != ']')
        return false;
    this->_index++;
    this->skipSpaces();
    if (this->_buffer.at(this->_index) == ']') {
        this->_index++;
        conf = Json::Value(arr);
        return true;
    }
    this->parseValue(tmp);
    arr.push_back(tmp);
    this->____MJsonReadArray(conf, arr);
    return true;
}
