#pragma once
#include <string>

namespace utils {

template <typename Error, typename Value>
class ErrorOr {

public:
    ErrorOr(Value&& value):
        value_(std::move(value)),
        is_error_(false) {

    }

    ErrorOr(Error error):
        is_error_(true),
        error_(error){

    }

    ErrorOr(Error error, const std::string& info):
        is_error_(true),
        error_(error),
        info_(info) {
    }

    operator bool() {
        return !is_error_;
    }

    Value& operator *() {
        return GetValue();
    }

    Value* operator->() {
        return &(GetValue());
    }


    Error getError() {
        return error_;
    }

    std::string getInfo() const {
        return info_;
    }

private:

    Value& GetValue() {
        return value_;
    }

    Value value_;

    bool is_error_;
    Error error_;
    std::string info_;
};


}
