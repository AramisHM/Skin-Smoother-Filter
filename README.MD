# Skin Smoother Filter (2017)
A C program to remove details/texture from the skin. It uses the LUX, CbCr color spaces and a bilateral fiilter to remove the details from the skin in 24bit .BMP files.

## Usage
Call the program with the 24bit .BMP file as argument.

![alt tag](https://github.com/AramisHM/Skin-Smoother-Filter/blob/master/doc/diagram.png)

Photo credits: JerzyGorecki

## Debugging
We recommend you to use Microsoft's Visual Studio Code with the following plugins:
C/C++ IntelliSense
CMake Tools
Code Runner

After configuring the CMake build kit, use F7 to build the project and F5 to debuf it.

You can also build de project with CMake CLI "cmake ." from root dir.