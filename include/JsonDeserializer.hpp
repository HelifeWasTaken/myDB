/**
 * File              : JsonDeserializer.hpp
 * Author            : Mattis DALLEAU <mattisdalleau@gmail.com>
 * Date              : 10.06.2021
 * Last Modified Date: 10.06.2021
 * Last Modified By  : Mattis DALLEAU <mattisdalleau@gmail.com>
 */
#pragma once

#include <JsonParser.hpp>

namespace jsonhl {

    class Deserializer : public Parser {
        private:
            Value _value;

            /**
             * @brief Read the current value passed at the array for the getter such as [4] if the string was badly written throws
             *
             * @param actualNode The current node for the search
             * @param it The iterator of the buffer string for the has and get determing how to look in the jsonhl::Values
             * @return true Suceeded to read the array
             * @return false Could not find an array object of type given in jsonhl::get or jsonhl::has
             */
            const bool ____MgetArray(jsonhl::Value& actualNode, std::string::iterator& it);

            /**
             * @brief Read the current value passed at the Object for the getter such as .name if the string was badly written throws
             *
             * @param actualNode The current node for the search
             * @param it The iterator of the buffer string for the has and get determing how to look in the jsonhl::Values
             * @return true Suceeded to read the Object
             * @return false Could not find an Object of type given in jsonhl::get or jsonhl::has
             */
            const bool ____MgetObject(jsonhl::Value& actualNode, std::string::iterator& it);

            /**
             * @brief Iterates over the whole buffer given in jsonhl::get or jsonhl::has to search for a particular node
             *        If the node is found actualNode is set to the node found and the function returns true if the buffer was badly written throws
             * @param buffer The string determing how to read the jsonhl::Value
             * @param actualNode The current node
             * @return true Found the node reasearched
             * @return false Did not found the node researched or one of the node was not an object or array type as expected
             */
            const bool ____MgetInternal(std::string& buffer, jsonhl::Value& actualNode);

        public:
            Deserializer();

            /**
             * @brief Get the Value object
             *
             * @return const Value&
             */
            const Value& getValue() const;

            /**
             * @brief Get a jsonhl::Value from a string
             *
             * @param buffer The string determing how to read the jsonhl::Value
             * @return const Value
             */
            const Value get(std::string buffer);

            /**
             * @brief Tells wether the jsonhl::Value exists from a string
             *
             * @param buffer The string determining how to read the jsonhl::Value
             * @return true has the node
             * @return false has not the node
             */
            const bool has(std::string buffer);

    };

};
