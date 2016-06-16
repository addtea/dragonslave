#include <iostream>

#include "app.hpp"
#include "error.hpp"

int main(int argc, char** argv) 
{
    try {
        dragonslave::App app;
        dragonslave::AppConfig app_config;
        app_config.title = "Lina is the best!";
        app.init(app_config);
        std::cout << "Press enter to exit." << std::endl;
        std::cin.getline(nullptr, 0);
        app.term();
    } catch (const dragonslave::FatalError& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }
    return 0;
}
