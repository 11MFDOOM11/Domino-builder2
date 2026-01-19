#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <chrono>
#include <filesystem>
#include <iomanip>
#include <sstream>

#include "dominolinebuilder.h"

int main()

{
	std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;
   const unsigned long int datasetSize = 5000;

   const std::string filepath = "dominoes-test_data/5000/5000-input.txt";

   std::ifstream theInputStream(filepath);
   if (! theInputStream.good()) throw std::runtime_error("Cannot read from specified file.");

   // Start timing the DominoLineBuilder construction
   auto constructionStart = std::chrono::high_resolution_clock::now();
   DominoLineBuilder theDominoLine(datasetSize,theInputStream);
   auto constructionEnd = std::chrono::high_resolution_clock::now();

   auto constructionDuration = std::chrono::duration_cast<std::chrono::microseconds>(constructionEnd - constructionStart);

   auto nextRightStart = std::chrono::high_resolution_clock::now();
   while (theDominoLine.nextRight());
   auto nextRightEnd = std::chrono::high_resolution_clock::now();

   // Calculate nextRight total time
   auto nextRightDuration = std::chrono::duration_cast<std::chrono::microseconds>(nextRightEnd - nextRightStart);

   //Start timing the displayLine operation
   auto displayStart = std::chrono::high_resolution_clock::now();
   theDominoLine.displayLine(std::cout);
   auto displayEnd = std::chrono::high_resolution_clock::now();
   std::cout << std::endl;

   auto displayDuration = std::chrono::duration_cast<std::chrono::microseconds>(displayEnd - displayStart);

   // Calculate total time
   auto totalDuration = constructionDuration + nextRightDuration + displayDuration;

   // Prepare performance results
   std::stringstream performanceReport;
   performanceReport << "\n========================================\n";
   performanceReport << "  DominoLineBuilder Performance Report  \n";
   performanceReport << "========================================\n";
   performanceReport << std::fixed << std::setprecision(3);
   performanceReport << "Dataset size:             " << std::setw(10) << datasetSize << " dominoes\n";
   performanceReport << "Construction time:        " << std::setw(10) << constructionDuration.count() / 1000.0 << " ms\n";
   performanceReport << "NextRight time:           " << std::setw(10) << nextRightDuration.count() / 1000.0 << " ms\n";
   performanceReport << "Display time:             " << std::setw(10) << displayDuration.count() / 1000.0 << " ms\n";
   performanceReport << "----------------------------------------\n";
   performanceReport << "Total execution time:     " << std::setw(10) << totalDuration.count() / 1000.0 << " ms\n";
   performanceReport << "========================================\n";

   // Output to console
   std::cout << performanceReport.str();

   // Output to file
   std::ofstream performanceFile("performance_results.txt");
   if (performanceFile.is_open())
   {
       performanceFile << "DominoLineBuilder Performance Results\n";
       auto now = std::chrono::system_clock::now();
       auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
       performanceFile << "Generated: " << ms << " ms since epoch\n";

       performanceFile << performanceReport.str();
       performanceFile.close();
       std::cout << "\nPerformance results saved to: performance_results.txt\n";
   }
   else
   {
       std::cerr << "Warning: Could not write performance results to file.\n";
   }

   return 0;
}
