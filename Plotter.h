#ifndef PLOTTER_H
#define PLOTTER_H

#include <vector>
#include <string>
#include <utility>

#include "PlotData.h"

class Plotter
{
public:
    static Plotter &getInstance();

    void plot(const std::string &name,
              const std::vector<Plot> &plots,
              const std::string &templatePath,
              const std::string &resultPath);

private:
    Plotter();
    Plotter(const Plotter &plotter) = delete;
    ~Plotter();

    static Plotter *instance;
};

#endif // PLOTTER_H
