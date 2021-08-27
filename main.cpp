#include <iostream>
#include <compare>
#include "db_config.h"

int main() {
    std::cout << "Hello world!" << std::endl;
    std::cout << "Version: " << Database_VERSION_MAJOR << "." << Database_VERSION_MINOR << std::endl;
    return 0;
}