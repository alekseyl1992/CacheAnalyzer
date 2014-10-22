#include "analyzer.h"
Analyzer *Analyzer::instance = nullptr;

Analyzer &Analyzer::getInstance()
{
    if (instance == nullptr)
        instance = new Analyzer();

    return *instance;
}

PlotData Analyzer::sequentialAccess(size_t padSize)
{

}

PlotData Analyzer::randomAccess(size_t padSize)
{

}

Analyzer::Analyzer()
{
}

Analyzer::~Analyzer()
{

}
