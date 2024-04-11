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

    unsigned char data[10] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A};
    err = ch340.bulk_write(EP_DATA_OUT, data, 10, 1000);
    if (err < 0) {
        std::cout << "Error writing data to CH340 device." << std::endl;
        return 1;
    }
    std::cout << "Data written to CH340 device." << std::endl;

    return 0;
}