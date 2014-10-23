#include "Plotter.h"

#include <fstream>
#include <sstream>
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

    //prepare data
    std::stringstream data;

    for (auto &plot: plots) {
        std::stringstream plotData;
        for (auto &point: plot.data)
            plotData << "[" << point.first << ", " << point.second << "], ";

        data << "(data.push({label: "
             << "PLS=" << plot.payloadSize
             << ", data: " << "[" << plotData.str() << "]});";
    }

    //write report
    std::string reportStr = (boost::format(buffer.str()) % data % name).str();
    std::ofstream report;
    report.write(reportStr.c_str(), reportStr.size());
}

Plotter::Plotter()
{
}

Plotter::~Plotter()
{

}
