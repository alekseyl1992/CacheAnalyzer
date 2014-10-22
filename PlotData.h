#ifndef PLOTDATA_H
#define PLOTDATA_H

#include <vector>
#include <utility>
#include <string>

typedef std::vector<std::pair<double, long>> PlotData;
struct Plot {
    std::string label;
    PlotData data;
};

#endif // PLOTDATA_H
