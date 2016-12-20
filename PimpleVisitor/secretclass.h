#ifndef SECRETCLASS_H
#define SECRETCLASS_H
#include <string>
#include <iostream>
class SecretClass {
public:
    SecretClass(const std::string& data);

    void foo();
    std::string data_;

};

#endif // SECRETCLASS_H
