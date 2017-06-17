#if __cplusplus > 201103L
#define DEPRECATED [[deprecated]]
#else 
#ifdef __GNUC__
#define DEPRECATED __attribute__((deprecated))
#define DEPRECATED_CLASS __attribute__((deprecated))
#elif defined(_MSC_VER)
#define DEPRECATED __declspec(deprecated)
#else
#pragma message("WARNING: You need to implement DEPRECATED for this compiler")
#define DEPRECATED
#endif
#endif

/**
 * @brief bar - raw deprecated function
 * @deprecated
 */
DEPRECATED void bar() {}

/**
 * @brief The X class containt one actual and one deprecated method
 * The class X is also deprecated
 * @deprecated
 */
class DEPRECATED X {

public:

    /**
     * @brief foo not deprecated function of deprecated class
     */
    void foo(){}

    /**
     * @brief bar deprecated function of deprecated class
     * @deprecated
     */
    DEPRECATED void bar(){}
};

/**
 * @brief The Y class containt one actual and one deprecated method
 */
class Y {

public:

    /**
     * @brief foo not deprecated function of not deprecated class
     */
    void foo(){}

    /**
     * @brief bar deprecated function of not deprecated class
     * @deprecated
     */
    DEPRECATED int bar(){}
};

class Parent {
public:
    /**
     * @brief foo deprecated virtual function
     */
     DEPRECATED virtual void foo() = 0;
};

class DEPRECATED DeprecatedParent {
public:
    /**
     * @brief bar virtual function of deprecated class
     */
     virtual void bar() {}
};

class Child : public Parent , public DeprecatedParent {
    // Parent interface
public:
    void foo(){}
};


int main() {
    bar();
    X x;
    x.foo();
    x.bar();

    Y y;
    y.foo();
    y.bar();

    Child c;
    c.foo();

    Parent* p = &c;
    p->foo();

    DeprecatedParent* dp = &c;
    dp->bar();

    return 0;
}

