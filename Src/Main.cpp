#include <iostream>
#include "WindowsTest.hpp"
#include "MacOSXTest.hpp"

int main(int argc, char** args)
{
    Test* t;
    
#ifdef SHADY_PLATFORM_WINDOWS
    t = new WindowsTest();
#endif // SHADY_PLATFORM_WINDOWS
    
#ifdef SHADY_PLATFORM_MAC_OSX
    t = new MacOSXTest();
#endif // SHADY_PLATFORM_MAC_OSX
    
    if (!t->initalize())
    {
        std::cout << "Initalization failed." << std::endl;
        return EXIT_FAILURE;
    }
    
    t->run();
    
    delete t;
}