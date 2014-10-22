#ifndef ANALYZER_H
#define ANALYZER_H

#include <PlotData.h>

class Analyzer
{
public:
    Analyzer &getInstance();

    PlotData sequentialAccess(size_t padSize);
    PlotData randomAccess(size_t padSize);

private:
    Analyzer();
    Analyzer(const Analyzer &analyzer) = delete;
    ~Analyzer();

    static Analyzer *instance;
};

#endif // ANALYZER_H
