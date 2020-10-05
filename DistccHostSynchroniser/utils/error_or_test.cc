#include <iostream>
#include "error_or.h"
#include <assert.h>

static std::string default_val;

class Val {
public:
    Val () : data_(default_val) {

    }

    Val (const std::string& data) : data_(data) {

    }

    Val (Val&& val) :
        data_(std::move(val.data_)) {

    }


    std::string data_;

private:
    Val (const Val& val) : data_(val.data_) {
        std::cout << "copy" << std::endl;
    }
};

enum ErrorType {
    ErrorType1,
    ErrorType2,
    ErrorType3,
};

int main (){

    {
        utils::ErrorOr<ErrorType, Val> err(ErrorType1);
        assert(!err);
        assert(err.getError() == ErrorType1);
        assert(err->data_ == default_val);
        assert(err.getInfo().empty());
    }
    {
        const std::string info = "info";
        utils::ErrorOr<ErrorType, Val> err(ErrorType1, info);
        assert(!err);
        assert(err.getError() == ErrorType1);
        assert(err->data_ == default_val);
        assert(err.getInfo() == info);
    }

    {
        const std::string str = "info";
        Val init(str);
        utils::ErrorOr<ErrorType, Val> err(std::move(init));
        assert(err);
        assert(err->data_ == str);
        assert(err.getInfo().empty());
        Val& res = *err;
        assert(res.data_ == str);

        Val res2 = std::move(*err);
        assert(res2.data_ == str);

    }

//    {
//        assert(err);
//        assert(err.getError() == ErrorType1);
//        assert(err.getError() == str);
//    }

//    {
//        assert(err);
//        assert(err.getError() == ErrorType1);
//        assert(err.getError() == str);
//    }

    return 0;
}
