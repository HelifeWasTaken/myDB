/**
 * File              : ValueGet.cpp
 * Author            : Mattis Dalleau <mattis.dalleau@epitech.eu>
 * Date              : 09.06.2021
 * Last Modified Date: 09.06.2021
 * Last Modified By  : Mattis Dalleau <mattis.dalleau@epitech.eu>
 */

#include <JsonValue.hpp>

const Json::Value::ValueType& Json::Value::getType() const {
    return this->_type;
}
const Json::Value::ValueHolder& Json::Value::getValue() const {
    return this->_value;
}
const double& Json::Value::getDouble() const {
    return std::get<double>(this->_value);
}
const std::int64_t Json::Value::getInteger() const {
    return static_cast<int64_t>(this->getDouble());
}
const bool& Json::Value::getBool() const {
    return std::get<bool>(this->_value);
}
const std::string& Json::Value::getStr() const {
    return std::get<std::string>(this->_value);
}
const Json::Value::Object& Json::Value::getObject() const {
    return std::get<Json::Value::Object>(this->_value);
}
const Json::Value::Array& Json::Value::getArray() const {
    return std::get<Json::Value::Array>(this->_value);
}
const Json::Value& Json::Value::operator[](std::string varName) const {
    return this->getObject().at(varName);
}
const Json::Value& Json::Value::operator[](int varIndex) const {
    return this->getArray().at(varIndex);
}
