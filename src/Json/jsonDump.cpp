/**
 * File              : jsonDump.cpp
 * Author            : Mattis DALLEAU <mattisdalleau@gmail.com>
 * Date              : 13.06.2021
 * Last Modified Date: 13.06.2021
 * Last Modified By  : Mattis DALLEAU <mattisdalleau@gmail.com>
 */
#include <JsonhlValue.hpp>

void jsonhl::printPadding(int& indentationLevel, std::ostream& os) {
    for (auto i = 0; i < indentationLevel; i++) {
        os << "    ";
    }
}

void jsonhl::dumpArray(const jsonhl::Value::Array& array, int& indentationLevel, std::ostream& os) {
    std::size_t i = 0;
    jsonhl::Value::ValueType lastType = jsonhl::Value::ValueType::JSONNULL;

    os << "[";
    while (i != array.size()) {
        jsonhl::dump(array[i], indentationLevel, os);
        lastType = array[i].getType();
        i++;
        if (i != array.size()) {
            os << ", ";
            if (lastType == jsonhl::Value::ValueType::OBJECT) {
                os << std::endl;
                jsonhl::printPadding(indentationLevel, os);
            }
        }
    }
    os << "]";
}

void jsonhl::dumpObject(const jsonhl::Value::Object& object, int& indentationLevel, std::ostream& os) {
    auto it = object.begin();

    os << "{" << std::endl;
    indentationLevel++;
    while (it != object.end()) {
        jsonhl::printPadding(indentationLevel, os);
        os << "\"" << it->first << "\": ";
        jsonhl::dump(it->second, indentationLevel, os);
        it++;
        if (it != object.end())
            os << "," << std::endl;
    }
    indentationLevel--;
    os << std::endl;
    jsonhl::printPadding(indentationLevel, os);
    os << "}";
}

void jsonhl::dumpStr(const std::string& buf, std::ostream& os) {
    os << "\"";
    for (auto i = 0; i < buf.size(); i++) {
        switch (buf[i]) {
            case '\a': os << "\\a"; break;
            case '\b': os << "\\b"; break;
            case '\t': os << "\\t"; break;
            case '\n': os << "\\n"; break;
            case '\v': os << "\\v"; break;
            case '\f': os << "\\f"; break;
            case '\r': os << "\\r"; break;
            default: os << buf[i]; break;
        }
    }
    os << "\"";
}

void jsonhl::dump(const jsonhl::Value& value, int& indentationLevel, std::ostream& os) {
    switch (value.getType()) {
        case jsonhl::Value::ValueType::ARRAY: jsonhl::dumpArray(value.getArray(), indentationLevel, os); break;
        case jsonhl::Value::ValueType::OBJECT: jsonhl::dumpObject(value.getObject(), indentationLevel, os); break;
        case jsonhl::Value::ValueType::STRING: jsonhl::dumpStr(value.getStr(), os); break;
        case jsonhl::Value::ValueType::BOOL: os << value.getBool(); break;
        case jsonhl::Value::ValueType::DOUBLE: os << value.getDouble(); break;
        case jsonhl::Value::ValueType::JSONNULL: os << "null"; break;
    }
}

void jsonhl::dump(const jsonhl::Value& value)
{
    int indentationLevel = 0;

    jsonhl::dump(value, indentationLevel, std::cout);
    std::cout << std::endl;
}
