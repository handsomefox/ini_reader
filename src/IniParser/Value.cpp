#include "Value.h"
#include "Utils.h"

Value::Value(std::string value)
        : _data(std::move(value)) {}

bool Value::Empty() const {
    return _data.empty();
}

std::string Value::ToString() const {
    return _data;
}

int32_t Value::ToInt32() const {
    if (_data.empty())
        return 0;

    return std::stoi(_data);
}

float Value::ToFloat() const {
    if (_data.empty())
        return 0.0f;

    return std::stof(_data);
}

double Value::ToDouble() const {
    if (_data.empty())
        return 0.0;

    return std::stod(_data);
}

bool Value::ToBool() const {
    bool is_alpha;

    if (contains(_data, '1') || contains(_data, '0'))
        is_alpha = false;
    else is_alpha = true;

    bool ret;

    if (is_alpha) std::istringstream(_data) >> std::boolalpha >> ret;
    else std::istringstream(_data) >> ret;

    return ret;
}
