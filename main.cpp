#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <filesystem>
#include <chrono>
#include <iomanip>

#include "dominolinebuilder.h"

void writePerformanceToCSV(const PerformanceMetrics& metrics, const std::string& filename)
{
   std::ofstream csvFile(filename);
   if (!csvFile.good())
   {
      std::cerr << "Warning: Could not write to CSV file: " << filename << std::endl;
      return;
   }

   csvFile << "Metric,Value_ms\n";
   csvFile << "Constructor," << std::fixed << std::setprecision(6) << metrics.constructorTime_ms << "\n";
   csvFile << "Total_NextRight," << metrics.totalNextRightTime_ms << "\n";
   csvFile << "DisplayLine," << metrics.displayLineTime_ms << "\n";
   csvFile << "Total_Dominoes," << metrics.totalDominoes << "\n";
   csvFile << "Dominoes_Placed," << metrics.dominoesPlaced << "\n";

   csvFile << "\nIteration,NextRight_Time_ms\n";
   for (size_t i = 0; i < metrics.nextRightTimes_ms.size(); ++i)
   {
      csvFile << i << "," << metrics.nextRightTimes_ms[i] << "\n";
   }

   csvFile.close();
   std::cout << "Performance data written to: " << filename << std::endl;
}

void displayPerformanceToConsole(const PerformanceMetrics& metrics, double totalExecutionTime_ms)
{
   std::cout << "\n\n========================================\n";
   std::cout << "    PERFORMANCE TIMING RESULTS\n";
   std::cout << "========================================\n\n";

   std::cout << std::fixed << std::setprecision(6);

   std::cout << "Constructor Time:         " << metrics.constructorTime_ms << " ms\n";
   std::cout << "Total NextRight Time:     " << metrics.totalNextRightTime_ms << " ms\n";
   std::cout << "Display Line Time:        " << metrics.displayLineTime_ms << " ms\n";
   std::cout << "Total Execution Time:     " << totalExecutionTime_ms << " ms\n\n";

   std::cout << "Total Dominoes:           " << metrics.totalDominoes << "\n";
   std::cout << "Dominoes Placed:          " << metrics.dominoesPlaced << "\n";
   std::cout << "NextRight Calls:          " << metrics.nextRightTimes_ms.size() << "\n\n";

   if (!metrics.nextRightTimes_ms.empty())
   {
      double avgNextRight = metrics.totalNextRightTime_ms / metrics.nextRightTimes_ms.size();
      double minTime = metrics.nextRightTimes_ms[0];
      double maxTime = metrics.nextRightTimes_ms[0];

      for (double time : metrics.nextRightTimes_ms)
      {
         if (time < minTime) minTime = time;
         if (time > maxTime) maxTime = time;
      }

      std::cout << "NextRight Statistics:\n";
      std::cout << "  Average:                " << avgNextRight << " ms\n";
      std::cout << "  Minimum:                " << minTime << " ms\n";
      std::cout << "  Maximum:                " << maxTime << " ms\n\n";
   }

   std::cout << "========================================\n\n";
}

int main()
{
   auto programStart = std::chrono::high_resolution_clock::now();

   std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;
   const unsigned long int datasetSize = 9;

   const std::string filepath = "example-input.txt";

   std::ifstream theInputStream(filepath);
   if (! theInputStream.good()) throw std::runtime_error("Cannot read from specified file.");

   DominoLineBuilder theDominoLine(datasetSize,theInputStream);

   while (theDominoLine.nextRight());

   std::cout << "\nDomino Line Result:\n";
   theDominoLine.displayLine(std::cout);
   std::cout << std::endl;

   auto programEnd = std::chrono::high_resolution_clock::now();
   std::chrono::duration<double, std::milli> totalDuration = programEnd - programStart;

   const PerformanceMetrics& metrics = theDominoLine.getPerformanceMetrics();

   displayPerformanceToConsole(metrics, totalDuration.count());
   writePerformanceToCSV(metrics, "domino_performance.csv");

   return 0;
}
