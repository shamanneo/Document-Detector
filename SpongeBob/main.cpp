#include <iostream>
#include "Foo.h"

int main()
{
    try
    {
        CFoo foo ; 
        foo.Run() ;
    }
    catch(cv::Exception &e)
    {
        std::cout << e.what() << std::endl ;  
    }
}

