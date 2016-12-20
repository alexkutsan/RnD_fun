#include "generator.h"
#include "secretclass.h"
#include "transferer_pimpl.h"

Tranferer Generator::Generate() {
    SecretClass* secret_class =
            new SecretClass("Send message to generator");
    return Tranferer::Impl::make_transferer(secret_class);
}
