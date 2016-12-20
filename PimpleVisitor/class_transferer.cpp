#include "class_tranferer.h"
#include "secretclass.h"
#include "transferer_pimpl.h"

void Tranferer::Visit(Visitor visitor) {
    visitor(*impl_);
}

Tranferer::Tranferer(std::unique_ptr<Tranferer::Impl> &impl):
    impl_(std::move(impl)) {

}

Tranferer::Tranferer(Tranferer &&from) = default;
Tranferer::~Tranferer() = default;
