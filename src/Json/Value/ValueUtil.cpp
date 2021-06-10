/**
 * File              : ValueUtil.cpp
 * Author            : Mattis Dalleau <mattis.dalleau@epitech.eu>
 * Date              : 09.06.2021
 * Last Modified Date: 09.06.2021
 * Last Modified By  : Mattis Dalleau <mattis.dalleau@epitech.eu>
 */

#include <JsonhlValue.hpp>

const char *jsonhl::Value::____MJsonValueToStr(const jsonhl::Value::ValueType &type) const
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
const jsonhl::Value::ValueType jsonhl::Value::____MGoodTypeOrThrow() const {
    if constexpr(std::is_same_v<T, double>) return jsonhl::Value::ValueType::DOUBLE;
    else if constexpr(std::is_same_v<T, int>) return jsonhl::Value::ValueType::DOUBLE;
    else if constexpr(std::is_same_v<T, bool>) return jsonhl::Value::ValueType::BOOLEAN;
    else if constexpr(std::is_same_v<T, std::string>) return jsonhl::Value::ValueType::STRING;
    else if constexpr(std::is_same_v<T, jsonhl::Value::Object>) return jsonhl::Value::ValueType::OBJECT;
    else if constexpr(std::is_same_v<T, jsonhl::Value::ARRAY>) return jsonhl::Value::ValueType::ARRAY;
    else if constexpr(std::is_same_v<T, void *>) return jsonhl::Value::ValueType::JSONNULL;
    else throw std::runtime_error("Maybe invalid use of jsonhl::Value::set<T>");
}
