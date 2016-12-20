#ifndef TRANSFERER_PIMPL_H
#define TRANSFERER_PIMPL_H
#include "class_tranferer.h"
#include "secretclass.h"
#include <memory>

class Tranferer::Impl {
public:
    Impl(SecretClass* ptr):secret_class_(ptr){}
    std::unique_ptr<SecretClass> secret_class_;
    ~Impl() = default;
    static Tranferer make_transferer(SecretClass* ptr) {
        auto impl = std::make_unique<Tranferer::Impl>(ptr);
        return Tranferer(impl);
    }

};


#endif // TRANSFERER_PIMPL_H

