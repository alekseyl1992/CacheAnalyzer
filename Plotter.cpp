#include "Plotter.h"
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
    //open template file

    //open new file

    //write header

    //write data

    //write footer

    //save

    //close
}

Plotter::Plotter()
{
}

Plotter::~Plotter()
{

}
