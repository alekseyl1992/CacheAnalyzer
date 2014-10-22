#ifndef ANALYZER_H
#define ANALYZER_H

#include <iostream>
#include <boost/preprocessor/repetition/repeat.hpp>
#include "PlotData.h"
#include "Measure.h"

#define REPEAT_COUNT 1 //256


template <size_t payloadSize>
class Analyzer
{
private:
    struct ArrayElement {
        ArrayElement(ArrayElement *next)
            : next(next)
        {}

        ArrayElement *next = nullptr;

        long payload[payloadSize];
    };

public:
    Analyzer(size_t minArraySizePower, size_t maxArraySizePower, size_t experimentsCount)
    {

    }

    Analyzer(const Analyzer &analyzer) = delete;

    ~Analyzer()
    {

    }

    double measureAccessTime(class ArrayElement *first, size_t arraySize)
    {
        return Measure<>::execution([&]() {
            for (size_t i = 0; i < accessCount; ++i) {
                #define CALL first = first->next;
                BOOST_PP_REPEAT(REPEAT_COUNT, CALL, 0);
            }
        });
    }

    PlotData sequentialAccess()
    {
        PlotData plotData;

        for (size_t arraySizePower = minArraySizePower;
             arraySizePower <= maxArraySizePower;
             ++arraySizePower) {
            size_t arraySize = 1 << arraySizePower; //fast power of 2
            ArrayElement *first = new ArrayElement[arraySize];

            //link sequentialy
            ArrayElement *cur = first;
            for (size_t i = 0; i < arraySize; ++i) {
                cur->next = first + i;
                ++cur;
            }

            //measure averaged access time
            double time = 0;
            for (size_t i = 0; i < experimentsCount; ++i) {
                time += measureAccessTime(first, arraySize);
            }
            time /= experimentsCount;

            plotData.push_back({time, arraySizePower + powerOf2ofArrayElement});

            delete[] first;
        }

        return plotData;
    }

    PlotData randomAccess()
    {
        PlotData plotData;

        return plotData;
    }

private:
    size_t powerOf2ofArrayElement = [](size_t size) {
        size_t power = 0;
        while (size >>= 1)
            ++power;

        return power;
    }(sizeof(ArrayElement));

    size_t minArraySizePower;
    size_t maxArraySizePower;
    size_t experimentsCount;  // per each array size
    size_t accessCount;  // TODO: pass via c-tor
};

#endif // ANALYZER_H
