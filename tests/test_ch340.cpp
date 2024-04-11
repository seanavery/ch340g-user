#include <iostream>
#include <cstdlib>
#include "ch340.h"

int main(int argc, char *argv[]) {
    std::cout << "Running ch340g library tests..." << std::endl;

    if (argc < 3) {
        std::cout << "Usage: " << argv[0] << " <vendor> <product>" << std::endl;
        std::cout << "Run lsusb to get the vendor and product id." << std::endl;
        return 1;
    }
    int product = std::stoi(argv[2]);
    int vendor = std::stoi(argv[1]);

    CH340 ch340;
    int err = ch340.init(product, vendor);
    
    if (err < 0) {
        std::cout << "Error initializing CH340 device." << std::endl;
        return 1;
    }
    std::cout << "CH340 device initialized." << std::endl;

    // test write
    // test read

    std::cout << "Tests completed." << std::endl;
    return 0;
}