#ifndef DOMINOLINEBUILDER_H
#define DOMINOLINEBUILDER_H

#include <iostream>
#include <vector>
#include <string>
#include <chrono>

struct Domino
{
   std::string blueSymbol;
   std::string redSymbol;

   Domino(std::string theBlueSymbol, std::string theRedSymbol);
};

struct PerformanceMetrics
{
   double constructorTime_ms;
   std::vector<double> nextRightTimes_ms;
   double totalNextRightTime_ms;
   double displayLineTime_ms;
   unsigned long int totalDominoes;
   unsigned long int dominoesPlaced;
};

class DominoLineBuilder
{
  public:
    DominoLineBuilder(unsigned long int totalNumberOfDominoes, std::istream& dominoInputData);
    bool nextRight();
    void displayLine(std::ostream& theOutputStream);
    const PerformanceMetrics& getPerformanceMetrics() const;

  private:
    std::vector<Domino> disorderedDominoes;
    std::vector<Domino> orderedLine;
    PerformanceMetrics metrics;
};

#endif
