#include "Engine.hpp"

int main()
{
    try {
        Engine app;
    }
    catch (...) {
        return 84;
    }
    return EXIT_SUCCESS;
}