#include <iostream>
#include "Video.h"
#include "Foo.h"

int main()
{
    try
    {
        CVideo video ; 
        video.Run() ; 
    }
    catch(cv::Exception &e)
    {
        std::cout << e.what() << std::endl ;  
    }
}

