/**
 * File              : DeserializerHas.cpp
 * Author            : Mattis DALLEAU <mattisdalleau@gmail.com>
 * Date              : 10.06.2021
 * Last Modified Date: 10.06.2021
 * Last Modified By  : Mattis DALLEAU <mattisdalleau@gmail.com>
 */
#include <JsonDeserializer.hpp>

const bool jsonhl::Deserializer::has(std::string buffer) {
    jsonhl::Value conf = this->_value;
    if (buffer.empty())
        throw std::runtime_error("Buffer is empty in jsonhl::Deserializer::has");
    return this->____MgetInternal(buffer, conf);
}
