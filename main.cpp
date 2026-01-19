#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <filesystem>

#include "dominolinebuilder.h"

int main()

{
	std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;
   const unsigned long int datasetSize = 9;

   const std::string filepath = "dominoes-test_data/example/example-input.txt";

   std::ifstream theInputStream(filepath);
   if (! theInputStream.good()) throw std::runtime_error("Cannot read from specified file.");

   DominoLineBuilder theDominoLine(datasetSize,theInputStream);

   while (theDominoLine.nextRight());

   theDominoLine.displayLine(std::cout);
}
