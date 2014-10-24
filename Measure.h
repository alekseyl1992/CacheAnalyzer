#ifndef MEASURE_H
#define MEASURE_H

#include <chrono>

template<typename TimeT = std::chrono::nanoseconds>
struct Measure
{
    template<typename F, typename ...Args>
    static typename TimeT::rep execution(F func, Args&&... args)
    {
        auto start = std::chrono::system_clock::now();

        // Now call the function with all the parameters you need.
        func(std::forward<Args>(args)...);

        auto duration = std::chrono::duration_cast<TimeT>
                            (std::chrono::system_clock::now() - start);

        return duration.count();
    }
};

#endif // MEASURE_H
