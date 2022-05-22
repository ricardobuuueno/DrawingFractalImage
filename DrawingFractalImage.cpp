// DrawingFractalImage.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "FractalCreator.h"

#include <memory>
#include <cmath>


int main()
{
    using fractaldrawing::Zoom;
    using fractaldrawing::FractalCreator;
    using fractaldrawing::RGB;

    FractalCreator fcreator(800, 600);

    fcreator.addRange(0.0, RGB(0, 0, 0));
    fcreator.addRange(0.3, RGB(255, 0, 0));
    fcreator.addRange(0.5, RGB(255, 255, 0));
    fcreator.addRange(1.0, RGB(255, 255, 255));

    fcreator.addZoom(Zoom(295, 202, 0.1));
    fcreator.addZoom(Zoom(312, 304, 0.1));

    fcreator.run("test.bmp");

    std::cout << "Finished!\n";

}

