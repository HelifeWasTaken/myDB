/**
 * File              : ParseObject.cpp
 * Author            : Mattis Dalleau <mattis.dalleau@epitech.eu>
 * Date              : 09.06.2021
 * Last Modified Date: 09.06.2021
 * Last Modified By  : Mattis Dalleau <mattis.dalleau@epitech.eu>
 */
#include <JsonParser.hpp>

void Json::Parser::____MJsonObjectReadData(Json::Value::Object& object) {
    Json::Value value;
    std::string key;

    this->skipSpaces();
    if (this->_buffer.at(this->_index) != '\"')
        throw "Could not find the start of the Key";
    this->_index++;
    this->____MJsonReadString(key);
    this->skipSpaces();
    if (this->_buffer.at(this->_index) != '\"')
        throw "Could not find the ':' determing the end of the Key";
    this->_index++;
    this->skipSpaces();
    this->parseValue(value);
    object[key] = value;
}

void Json::Parser::____MJsonParseObjectLoop(Json::Value& conf, Json::Value::Object& objects) {
    this->____MJsonObjectReadData(objects);
    while (this->_buffer.at(this->_index)) {
        this->skipSpaces();
        if (this->_buffer.at(this->_index) == '}') {
            conf = Value(objects);
            this->_index++;
            return;
        } else if (this->_buffer.at(this->_index) != ',')
            throw "expected ',' after value [object]";
        this->_index++;
        this->skipSpaces();
        this->____MJsonObjectReadData(objects);
    }
    throw "Expected '}' at the end of the object";
}

bool Json::Parser::parseObject(Json::Value& conf) {
    Json::Value::Object objects;

    if (this->_buffer.at(this->_index) != '{')
        return false;
    this->_index++;
    this->skipSpaces();
    if (this->_buffer.at(this->_index) != '}') {
        this->_index++;
        conf = Value(objects);
        return true;
    }
    this->____MJsonParseObjectLoop(conf, objects);
    return true;
}