#include "Plotter.h"

#include <fstream>
#include <sstream>
#include <string>
#include <boost/format.hpp>

Plotter *Plotter::instance = nullptr;

Plotter &Plotter::getInstance()
{
    if (instance == nullptr)
        instance = new Plotter();

    return *instance;
}

void Plotter::plot(const std::string &name,
                   const std::vector<Plot> &plots,
                   const std::string &templatePath,
                   const std::string &resultPath)
{
    //read template file
    std::ifstream t(templatePath);
    std::stringstream buffer;
    buffer << t.rdbuf();
    t.close();

    //prepare data
    std::stringstream data;

    for (auto &plot: plots) {
        std::stringstream plotData;
        for (auto &point: plot.data)
            plotData << "[" << point.second << ", " << point.first << "], ";

        data << (boost::format(R"(data.push({label: "PLS=%s", data: [%s]});)")
                % plot.payloadSize
                % plotData.str()).str();
        data << std::endl;
    }

    //write report
    std::string reportStr = (boost::format(buffer.str()) %name % data.str() % name).str();

    std::ofstream report(resultPath);
    report << reportStr;
    report.close();
}

Plotter::Plotter()
{
}

Plotter::~Plotter()
{

}
