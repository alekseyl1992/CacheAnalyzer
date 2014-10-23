#include <iostream>
#include <memory>
#include "Analyzer.h"
#include "Plotter.h"

template <size_t... sizes> createAnalyzers(size_t minArraySizePower,
                                           size_t maxArraySizePower,
                                           size_t experimentsCount,
                                           size_t accessCount)
{
    [](...){}((analyze(std::make_shared<Analyzer<sizes>>(minArraySizePower,
                                                         maxArraySizePower,
                                                         experimentsCount,
                                                         accessCount)), 0)...);
}

template <typename T>
void analyze(std::shared_ptr<T> analyzer)
{
    //analyzer->test();
}

int main()
{
    size_t minArraySizePower = 2;
    size_t maxArraySizePower = 20;
    size_t experimentsCount = 10;
    size_t accessCount = 1024;

    createAnalyzers<7, 15, 31, 63>(minArraySizePower,
                                   maxArraySizePower,
                                   experimentsCount,
                                   accessCount);
}
