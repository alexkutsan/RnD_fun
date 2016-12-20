#ifndef CLASS_TRANFERER_H
#define CLASS_TRANFERER_H
#include <memory>
#include <functional>
#include <iostream>

class Tranferer {
public:
    class Impl;

    std::unique_ptr<Impl> impl_;
    typedef std::function<void(Impl&)> Visitor;
    void Visit(Visitor visitor);
    ~Tranferer();

    Tranferer(Tranferer&& from);
    Tranferer(std::unique_ptr<Impl> &impl);
    Tranferer(const Tranferer& copy) = delete;
    Tranferer& operator = (const Tranferer& copy) = delete;
};

#endif // CLASS_TRANFERER_H

