#pragma once

#include <cinttypes>
#include <map>
#include <vector>
#include <memory>
#include <iostream>
#include <variant>

namespace Json {

    class Value {
        public:
            typedef std::map<std::string, Value> Object;
            typedef std::vector<Value> Array;
            typedef std::variant<double, bool, std::string,
                                Object, Array, void *> ValueHolder;
            enum ValueType {
                DOUBLE,
                BOOL,
                STRING,
                OBJECT,
                ARRAY,
                JSONNULL,
                INTEGER = DOUBLE,
                FLOAT   = DOUBLE,
                REAL    = DOUBLE,
                BOOLEAN = BOOL,
            };

        private:
            ValueHolder _value;
            ValueType _type;

        /* Value/ValueUtil.cpp */
        private:
            /**
             * @brief Returns as a char * the name of the type currently used
             *
             * @param type The type used
             * @return const char* The name of the type passing Json::Value::ValueType::STRING returns "STRING"
             */
            const char *____MJsonValueToStr(const ValueType &type) const;

            /**
             * @brief Throws if the type passed in the constructor is invalid also returns the current type as Json::Value::ValueType
             *
             * @tparam T The value
             * @return ValueType the type of the value
             */
            template <typename T>
            ValueType ____MGoodTypeOrThrow() const;

        /* Value/Value.cpp */
        public:
            /**
             * @brief Construct a new Value object
             *
             * @param value
             */
            Value(const double& value);
            /**
             * @brief Construct a new Value object
             *
             * @param value
             */
            Value(const int& value);
            /**
             * @brief Construct a new Value object
             *
             * @param value
             */
            Value(const bool& value);
            /**
             * @brief Construct a new Value object
             *
             * @param value
             */
            Value(const std::string& value);
            /**
             * @brief Construct a new Value object
             *
             * @param value
             */
            Value(const Array& value);
            /**
             * @brief Construct a new Value object
             *
             * @param value
             */
            Value(const Object& value);
            /**
             * @brief Construct a new Value object from Template (It throws if an invalid type is chosen)
             *
             * @tparam T
             * @param value
             */
            template <typename T>
            Value(const T& value);
            /**
             * @brief Construct a new Value object (create a nullvalue by default)
             *
             */
            Value();

            /**
             * @brief Destroy the Value object
             *
             */
            ~Value();

            /**
             * @brief Set the Json::Value value from Template (if a invalid type is chose it throws)
             */

        /* Value/ValueSet.cpp */
        public:
            template <typename T>
            void set(const T& value);

        /* Value/ValueGet.cpp */
        public:
            /**
             * @brief Get the Type object
             *
             * @return const ValueType&
             */
            const ValueType& getType() const;
            /**
             * @brief Get the Value object
             *
             * @return const ValueHolder&
             */
            const ValueHolder& getValue() const;
            /**
             * @brief Get the Double object (it throws if the type of _value is not the same)
             *
             * @return const double&
             */
            const double& getDouble() const;
            /**
             * @brief Get the Integer object (it throws if the type of _value is not the same)
             *
             * @return const std::int64_t
             */
            const std::int64_t getInteger() const;
            /**
             * @brief Get the Bool object (it throws if the type of _value is not the same)
             *
             * @return true
             * @return false
             */
            const bool& getBool() const;
            /**
             * @brief Get the Str object (it throws if the type of _value is not the same)
             *
             * @return const std::string&
             */
            const std::string& getStr() const;
            /**
             * @brief Get the Object object (it throws if the type of _value is not the same)
             *
             * @return const Object&
             */
            const Object& getObject() const;
            /**
             * @brief Get the Array object (it throws if the type of _value is not the same)
             *
             * @return const Array&
             */
            const Array& getArray() const;
            /**
             * @brief Get the Array Raw object (it throws if the type of _value is not the same)
             *
             * @return Array*
             */
            Array *getArrayRaw() const;

            /**
             * @brief Tells wether the current value is JsonNull value
             *
             * @return true Is a JsonNull value
             * @return false Is not a JsonNull value
             */

        /* Value/ValueIs.cpp */
        public:
            const bool isNull() const;
            /**
             * @brief Check if the type of the current _value is the same as type passed as argument
             *
             * @param type The argument seeked
             * @return true Is of the same type
             * @return false Is not of the same type
             */
            const bool is(const ValueType& type) const;

    };

};