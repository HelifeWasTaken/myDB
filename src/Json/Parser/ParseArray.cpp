/**
 * File              : ParseArray.cpp
 * Author            : Mattis Dalleau <mattis.dalleau@epitech.eu>
 * Date              : 09.06.2021
 * Last Modified Date: 10.06.2021
 * Last Modified By  : Mattis DALLEAU <mattisdalleau@gmail.com>
 */
#include <JsonhlParser.hpp>

void jsonhl::Parser::____MJsonReadArray(jsonhl::Value& conf, jsonhl::Value::Array& arr) {
    jsonhl::Value tmp;

    while (this->_buffer.at(this->_index)) {
        this->skipSpaces();
        if (this->_buffer.at(this->_index) == ']') {
            this->_index++;
            conf = jsonhl::Value(arr);
            return;
        }
        if (this->_buffer.at(this->_index) != ',')
            throw std::runtime_error("Expected ',' after value [array]");
        this->_index++;
        this->parseValue(tmp);
        arr.push_back(tmp);
        tmp = jsonhl::Value();
    }
    throw std::runtime_error("Expected ']' at the end of the array");
}

bool jsonhl::Parser::parseArray(jsonhl::Value& conf) {
    jsonhl::Value tmp;
    jsonhl::Value::Array arr;

    if (this->_buffer.at(this->_index) != '[')
        return false;
    this->_index++;
    this->skipSpaces();
    if (this->_buffer.at(this->_index) == ']') {
        this->_index++;
        conf = jsonhl::Value(arr);
        return true;
    }
    this->parseValue(tmp);
    arr.push_back(tmp);
    this->____MJsonReadArray(conf, arr);
    return true;
}
