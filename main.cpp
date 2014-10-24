#include <iostream>
#include <memory>
#include "Analyzer.h"
#include "Plotter.h"

std::vector<Plot> sequentialPlots, randomPlots;

template <size_t... sizes>
void createAnalyzers(size_t minArraySizePower,
                     size_t maxArraySizePower,
                     size_t experimentsCount,
                     size_t accessCount)
{
    [](...){}((analyze(std::make_shared<Analyzer<sizes>>(minArraySizePower,
                                                         maxArraySizePower,
                                                         experimentsCount,
                                                         accessCount)), 0)...);
}

template <typename T>
void analyze(std::shared_ptr<T> analyzer)
{
    std::cout << "Analyzing with PLS: " << analyzer->getPayloadSize() << std::endl;

    sequentialPlots.push_back({analyzer->getPayloadSize(),
                               analyzer->sequentialAccess()});

    randomPlots.push_back({analyzer->getPayloadSize(),
                           analyzer->randomAccess()});
}

int main()
{
    size_t minArraySizePower = 2;
    size_t maxArraySizePower = 22;
    size_t experimentsCount = 100;
    size_t accessCount = 1024*REPEAT_COUNT;

    std::cout << "CacheAnalyzer started" << std::endl;
    std::cout << "---------------------" << std::endl;

    createAnalyzers<7, 15, 31, 63, 127, 255>(minArraySizePower,
                                   maxArraySizePower,
                                   experimentsCount,
                                   accessCount);

    std::cout << "---------------------" << std::endl;

    //save data
    std::string reportsPath = "./reports/";
    std::string templatePath = reportsPath + "template.html";

    std::cout << "Plotting sequential access" << std::endl;
    Plotter::getInstance().plot("Sequential access",
                               sequentialPlots,
                               templatePath,
                               reportsPath + "sequentialAccess.html");

    std::cout << "Plotting random access" << std::endl;
    Plotter::getInstance().plot("Random access",
                           randomPlots,
                           templatePath,
                           reportsPath + "randomAccess.html");

    std::cout << "---------------------" << std::endl;
    std::cout << "CacheAnalyzer finished" << std::endl;
}
