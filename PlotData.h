#ifndef PLOTDATA_H
#define PLOTDATA_H

#include <vector>
#include <utility>
#include <string>

typedef std::vector<std::pair<double, size_t>> PlotData;
struct Plot {
    size_t payloadSize;
    PlotData data;
};

#endif // PLOTDATA_H
