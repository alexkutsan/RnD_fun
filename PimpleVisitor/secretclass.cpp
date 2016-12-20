#include "secretclass.h"
#include <iostream>
SecretClass::SecretClass(const std::string &data):data_(data) {}

void SecretClass::foo() {
    std::cout << data_ << std::endl;
}

