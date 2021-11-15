#include <iostream>
#include "mandelbrot.h"

int main(int argc, char* args[]) {
    Mandelbrot mb;
    
    if (mb.Initialize()) {
        mb.RunLoop();
    }
    else {
        std::cout << "Failed to initialize";
    }
    
    mb.End();
    return 0;
}
