#include "Engine.hpp"

int main()
{
    try {
        Engine app;
        return app.start();
    }
    catch (...) {
        return 84;
    }
}