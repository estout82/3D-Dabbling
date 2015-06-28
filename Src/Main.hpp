#ifndef MAIN_HPP
#define MAIN_HPP

//#define SHADY_PLATFORM_WINDOWS
#define SHADY_PLATFORM_MAC_OSX

class Test
{
public:
    Test() {}
    
    virtual ~Test() {}
    
    virtual bool initalize() = 0;
    virtual void run() = 0;
    
private:
};

#endif