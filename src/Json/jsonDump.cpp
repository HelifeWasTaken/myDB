#include <JsonhlValue.hpp>

void jsonhl::printPadding(int& indentationLevel) {
    for (auto i = 0; i < indentationLevel; i++) {
        std::cout << "    ";
    }
}

void jsonhl::dumpArray(const jsonhl::Value::Array& array, int& indentationLevel) {
    std::size_t i = 0;

    std::cout << "[" << std::endl;
    indentationLevel++;
    jsonhl::printPadding(indentationLevel);
    while (i != array.size()) {
        jsonhl::dump(array[i], indentationLevel);
        i++;
        if (i != array.size())
            std::cout << ", ";
    }
    indentationLevel--;
    std::cout << "]";
}

void jsonhl::dumpObject(const jsonhl::Value::Object& object, int& indentationLevel) {
    auto it = object.begin();

    std::cout << "{" << std::endl;
    indentationLevel++;
    while (it != object.end()) {
        jsonhl::printPadding(indentationLevel);
        std::cout << "\"" << it->first << "\": ";
        jsonhl::dump(it->second, indentationLevel);
        it++;
        if (it != object.end())
            std::cout << "," << std::endl;
    }
    indentationLevel--;
    std::cout << std::endl;
    jsonhl::printPadding(indentationLevel);
    std::cout << "}";
}

void jsonhl::dumpStr(const std::string& buf) {
    std::cout << "\"";
    for (auto i = 0; i < buf.size(); i++) {
        switch (buf[i]) {
            case '\a': std::cout << "\\a"; break;
            case '\b': std::cout << "\\b"; break;
            case '\t': std::cout << "\\t"; break;
            case '\n': std::cout << "\\n"; break;
            case '\v': std::cout << "\\v"; break;
            case '\f': std::cout << "\\f"; break;
            case '\r': std::cout << "\\r"; break;
            default: std::cout << buf[i]; break;
        }
    }
    std::cout << "\"";
}

void jsonhl::dump(const jsonhl::Value& value, int& indentationLevel) {
    switch (value.getType()) {
        case jsonhl::Value::ValueType::ARRAY: jsonhl::dumpArray(value.getArray(), indentationLevel); break;
        case jsonhl::Value::ValueType::OBJECT: jsonhl::dumpObject(value.getObject(), indentationLevel); break;
        case jsonhl::Value::ValueType::STRING: jsonhl::dumpStr(value.getStr()); break;
        case jsonhl::Value::ValueType::BOOL: std::cout << value.getBool(); break;
        case jsonhl::Value::ValueType::DOUBLE: std::cout << value.getDouble(); break;
        case jsonhl::Value::ValueType::JSONNULL: std::cout << "null"; break;
    }
}

void jsonhl::dump(const jsonhl::Value& value)
{
    int indentationLevel = 0;

    jsonhl::dump(value, indentationLevel);
    std::cout << std::endl;
}
