# Rastersoft

## Introduction

Rastersoft is a simple single threaded/CPU 3D renderer. The goal of creating Rastersoft is to learn the math and theory of computer graphics before moving on to realistic applications.

Currently, I only plan to implement Rastersoft on Windows, but I may add Linux support in the future.

## Table of Contents

- [Rastersoft](#rastersoft)
    - [Introduction](#introduction)
    - [Table of Contents](#table-of-contents)
    - [Dev Environment Setup](#dev-environment-setup)
        - [SDL2](#sdl2)
        - [CMAKE](#cmake)
    - [License](#license)

## Dev Environment Setup

### SDL2

The Rastersoft library itself does not require [SDL2](https://www.libsdl.org/index.php). However, the demo is built using SDL2 for pixel access and some controls.

- Download the [SDL2 Development Libraries](https://www.libsdl.org/download-2.0.php) for Visual C++ 32/64bit
- Unzip the SDL2 somewhere on your system.
- Set the **SDL2** environment variable to the root of the development libraries folder.
    - Example: use command to set EV.
    ``` cmd
    set SDL2=C:\SDL2-2.0.7
    ```
    - This allows CMAKE to find SDL2 when generating the build system.

### CMAKE

CMAKE is used to generate a Visual Studio solution, which can then build the project.

- Install [CMAKE](https://cmake.org/download/) and add it to your user or system PATH.
- From the root directory of the repository.
    - Create the build directory where the build system and CMAKE files will be stored
        ``` cmd
        mkdir build
        ```
    - To generate the build system, run the following command from the root directory of the repository.
        - If you are using another version of Visual Studio, change the [Generator](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html) string to match the version.
        ``` cmd
        cmake -G"Visual Studio 15 2017 Win64" -B./build -H.
        ```

Note: If you wish to 'Clean' and regenerate the build system from scratch, just delete and recreate the 'build' directory.

## License

Rastersoft uses the MIT License. Feel free to use my code in whatever way you wish. I would appreciate giving me credit if you use it in a project, but it is not necessary.