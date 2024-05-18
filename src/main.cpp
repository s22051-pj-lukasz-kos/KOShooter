#include <iostream>
#include "App.h"

App app;

int main() {
    try {
        app.run();
    } catch (const std::exception &e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}