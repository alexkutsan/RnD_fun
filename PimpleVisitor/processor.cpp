#include "processor.h"
#include "transferer_pimpl.h"
#include "secretclass.h"

void Processor::Process(const Tranferer &transferer) {
   std::unique_ptr<SecretClass> secret_class =
           std::move(transferer.impl_->secret_class_);
   secret_class->foo();
}
