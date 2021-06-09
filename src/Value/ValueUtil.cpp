/**
 * File              : ValueUtil.cpp
 * Author            : Mattis Dalleau <mattis.dalleau@epitech.eu>
 * Date              : 09.06.2021
 * Last Modified Date: 09.06.2021
 * Last Modified By  : Mattis Dalleau <mattis.dalleau@epitech.eu>
 */

#include <JsonValue.hpp>

const char *Json::Value::____MJsonValueToStr(const Json::Value::ValueType &type) const
{
    switch (type) {
        case DOUBLE: return "float";
        case BOOL: return "boolean";
        case STRING: return "string";
        case OBJECT: return "object";
        case ARRAY: return "array";
    }
    return "N/A";
}

template <typename T>
Json::Value::ValueType Json::Value::____MGoodTypeOrThrow() const {
    if constexpr(std::is_same_v<T, double>) return Json::Value::ValueType::DOUBLE;
    else if constexpr(std::is_same_v<T, int>) return Json::Value::ValueType::DOUBLE;
    else if constexpr(std::is_same_v<T, bool>) return Json::Value::ValueType::BOOLEAN;
    else if constexpr(std::is_same_v<T, std::string>) return Json::Value::ValueType::STRING;
    else if constexpr(std::is_same_v<T, Json::Value::Object>) return Json::Value::ValueType::OBJECT;
    else if constexpr(std::is_same_v<T, Json::Value::ARRAY>) return Json::Value::ValueType::ARRAY;
    else if constexpr(std::is_same_v<T, void *>) return Json::Value::ValueType::JSONNULL;
    else throw "Maybe invalid use of Json::Value::set<T>";
}