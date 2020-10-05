#pragma once
#include <string>

namespace utils {
class Hash {

    std::string asString() {
        return "Xyz";
    }
};

inline Hash GenerateHash(const Hash& prev_hash, std::string data) {
    return Hash();
}

}

