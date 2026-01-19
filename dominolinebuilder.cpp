#include "dominolinebuilder.h"

Domino::Domino(std::string theBlueSymbol, std::string theRedSymbol)
{
   blueSymbol = theBlueSymbol;
   redSymbol = theRedSymbol;
}

DominoLineBuilder::DominoLineBuilder(unsigned long int totalNumberOfDominoes, std::istream& dominoInputData)
{
   auto start = std::chrono::high_resolution_clock::now();

   metrics.totalDominoes = totalNumberOfDominoes;
   metrics.dominoesPlaced = 0;
   metrics.totalNextRightTime_ms = 0.0;

   for (unsigned long int i = 0; i < totalNumberOfDominoes; ++i)
   {
       std::string aBlueSymbol, aRedSymbol;
       std::getline(dominoInputData, aBlueSymbol, ':');
       std::getline(dominoInputData, aRedSymbol, '\n');

       disorderedDominoes.push_back(Domino(aBlueSymbol,aRedSymbol));
   }

   auto end = std::chrono::high_resolution_clock::now();
   std::chrono::duration<double, std::milli> duration = end - start;
   metrics.constructorTime_ms = duration.count();
}

bool DominoLineBuilder::nextRight()
{
   auto start = std::chrono::high_resolution_clock::now();

   bool result = false;

   if (orderedLine.empty())
   {
      orderedLine.push_back(disorderedDominoes.back());
      disorderedDominoes.pop_back();
      result = true;
   }
   else
   {
      for (Domino currentDomino : disorderedDominoes)
      {
         if (currentDomino.blueSymbol == orderedLine.back().redSymbol)
         {
            orderedLine.push_back(currentDomino);
            result = true;
            break;
         }
      }
   }

   auto end = std::chrono::high_resolution_clock::now();
   std::chrono::duration<double, std::milli> duration = end - start;
   double elapsed_ms = duration.count();

   metrics.nextRightTimes_ms.push_back(elapsed_ms);
   metrics.totalNextRightTime_ms += elapsed_ms;

   if (result)
   {
      metrics.dominoesPlaced++;
   }

   return result;
}

void DominoLineBuilder::displayLine(std::ostream& outputStream)
{
   auto start = std::chrono::high_resolution_clock::now();

   for (Domino eachDomino : orderedLine)
   {
      outputStream << eachDomino.blueSymbol << ':' << eachDomino.redSymbol << ' ';
   }

   auto end = std::chrono::high_resolution_clock::now();
   std::chrono::duration<double, std::milli> duration = end - start;
   metrics.displayLineTime_ms = duration.count();
}

const PerformanceMetrics& DominoLineBuilder::getPerformanceMetrics() const
{
   return metrics;
}
