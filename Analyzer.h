#ifndef ANALYZER_H
#define ANALYZER_H

#include <iostream>
#include <algorithm>
#include <functional>
#include <stdint.h>
#include <boost/preprocessor/repetition/repeat.hpp>
#include "PlotData.h"
#include "Measure.h"

#define REPEAT_COUNT 1 //256


template <size_t payloadSize>
class Analyzer
{
private:
    struct ArrayElement {
        ArrayElement *next = nullptr;
        std::conditional<sizeof(ArrayElement *) == 4, uint32_t, uint64_t> payload[payloadSize];
    };

public:
    Analyzer(size_t minArraySizePower,
             size_t maxArraySizePower,
             size_t experimentsCount,
             size_t accessCount)
        : minArraySizePower(minArraySizePower),
          maxArraySizePower(maxArraySizePower),
          experimentsCount(experimentsCount),
          accessCount(accessCount / REPEAT_COUNT)
    {

    }

    Analyzer(const Analyzer &analyzer) = delete;

    ~Analyzer()
    {

    }

    size_t getPayloadSize() const
    {
        return payloadSize;
    }

    double measureAccessTime(class ArrayElement *first, size_t arraySize)
    {
        return Measure<>::execution([&]() {
            for (size_t i = 0; i < accessCount; ++i) {
                #define CALL first = first->next;
                BOOST_PP_REPEAT(REPEAT_COUNT, CALL, 0);
            }
        }) / (accessCount * REPEAT_COUNT);
    }

    PlotData access(std::function<void(ArrayElement *, size_t)> linker)
    {
        PlotData plotData;

        for (size_t arraySizePower = minArraySizePower;
             arraySizePower <= maxArraySizePower;
             ++arraySizePower) {
            size_t arraySize = 1 << arraySizePower; //fast power of 2
            ArrayElement *first = new ArrayElement[arraySize];

            //link elements
            linker(first, arraySize);

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

    PlotData sequentialAccess()
    {
        return access([](ArrayElement *first, size_t arraySize) {
            //link sequentialy
            ArrayElement *cur = first;
            for (size_t i = 1; i < arraySize; ++i) {
                cur->next = first + i;
                ++cur;
            }
            cur->next = first;  // make a loop
        });
    }

    PlotData randomAccess()
    {
        return access([](ArrayElement *first, size_t arraySize) {
            //link randomly all elements
            std::vector<size_t> offsets(arraySize);
            std::iota(offsets.begin(), offsets.end(), 0);

            std::random_device rd;
            std::mt19937 g(rd());
            std::shuffle(offsets.begin(), offsets.end(), g);

            ArrayElement *cur = first;
            for (size_t i = 1; i < arraySize; ++i) {
                cur->next = first + offsets[i];
                ++cur;
            }
        });
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
    size_t accessCount;  //access count in 1 experiment
};

#endif // ANALYZER_H
