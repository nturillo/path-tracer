#include <iostream> 

#include "color.hpp"
#include "vec3.hpp"

int main() {
    //image
    const int
        IMAGE_WIDTH = 1024,
        IMAGE_HEIGHT = 768;
    
    //Render image:
    //header
    std::cout << "P3\n" << IMAGE_WIDTH << " " << IMAGE_HEIGHT << "\n255\n";

    //body
    for (int row = 0; row < IMAGE_HEIGHT; row++) {
        for (int col = 0; col < IMAGE_WIDTH; col++) {
            //progress bar
            //std::clog << "\rScanlines remaining: " << IMAGE_HEIGHT - row << " " << std::flush;
            //pixel color

            color pixel = color(double(col) / (IMAGE_WIDTH - 1), double(row) / (IMAGE_HEIGHT - 1), 0.0);

            write_color(std::cout, pixel);
        }
    }
}