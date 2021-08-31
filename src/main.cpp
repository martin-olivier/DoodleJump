#include <iostream>
#include "Core.hpp"

int main()
{
    try {
        Core app;
    }
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    catch (...) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}