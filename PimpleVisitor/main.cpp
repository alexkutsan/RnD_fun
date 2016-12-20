#include <iostream>
#include "generator.h"
#include "processor.h"

using namespace std;

int main()
{
    Generator g;
    Processor p;
    Tranferer data(g.Generate());
    p.Process(data);
    return 0;
}

