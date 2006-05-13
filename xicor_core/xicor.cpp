#include "core/core.h"

#include <iostream>

using namespace xicor;
using namespace xicor::core;

int main (int argc, char** argv)
{
    try {
        Core core;
        core.init();
        std::cout << "Core initialized" << std::endl;
        core.serialize(std::cout);
        core.start();
        std::cout << "Core stopped" << std::endl;
    }
    catch (const Exception& ex) {
        std::cout   << ex.getModuleName() << ":" << std::endl
                    << ex.getMessage() << std::endl;
        std::cout   << "Location: " 
                    << ex.getLocation().filename << " -- "
                    << ex.getLocation().line_num << std::endl;
    }
    catch (...) {
        std::cout << "Unknown exception" << std::endl;
    }
    std::cout << "Core is deinitialized" << std::endl;
    return 0;
}
