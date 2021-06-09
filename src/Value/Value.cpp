/**
 * File              : Value.cpp
 * Author            : Mattis Dalleau <mattis.dalleau@epitech.eu>
 * Date              : 09.06.2021
 * Last Modified Date: 09.06.2021
 * Last Modified By  : Mattis Dalleau <mattis.dalleau@epitech.eu>
 */

#include <JsonValue.hpp>

Json::Value::Value(const double& value) : _value(value), _type(Json::Value::ValueType::DOUBLE) {}
Json::Value::Value(const int& value) { *this = Value(static_cast<double>(value)); }
Json::Value::Value(const bool& value) : _value(value), _type(Json::Value::ValueType::BOOL) {}
Json::Value::Value(const std::string& value) : _value(value), _type(Json::Value::ValueType::STRING) {}
Json::Value::Value(const Json::Value::Array& value) : _value(value), _type(Json::Value::ValueType::ARRAY) {}
Json::Value::Value(const Json::Value::Object& value) : _value(value), _type(Json::Value::ValueType::OBJECT) {}
template <typename T>
Json::Value::Value(const T& value) : _value(value), _type(this->____MGoodTypeOrThrow<T>()) { }
Json::Value::Value() : _value(nullptr), _type(Json::Value::ValueType::JSONNULL) {}

Json::Value::~Value() {}