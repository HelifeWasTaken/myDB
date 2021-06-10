/**
 * File              : ValueSet.cpp
 * Author            : Mattis Dalleau <mattis.dalleau@epitech.eu>
 * Date              : 09.06.2021
 * Last Modified Date: 09.06.2021
 * Last Modified By  : Mattis Dalleau <mattis.dalleau@epitech.eu>
 */

#include <JsonValue.hpp>

template <typename T>
void jsonhl::Value::set(const T& value) {
    *this = jsonhl::Value(value);
}