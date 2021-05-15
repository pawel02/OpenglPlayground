# About
This project was made to learn more about C++, Cmake, OpenGL, GLSL, Game Engines

# Structure
The Engine project creates a library which is linked against in the examples. The engine contains some very useful OpenGL Abstractions to make it easier to work with.

# Building
Before building the project you will need to make sure that you have all of the necessary submodules so run the command \
`git submodule update --init --recursive`

To build the project you will need to have CMake installed on your machine \
Then you can run the following command \
`cmake -S . -B ./build -DBUILD_SHARED_LIBS=OFF -DASSIMP_BUILD_ZLIB=ON` \
\
You can then build your solution on windows or the make files on Linux or whatever build system you are targeted on Cmake. 
On windows it would look something like. You may need to build the whole solution first to create the necessary lib files as well. \
`cd build` \
`msbuild Playground.sln /p:configuration=Debug /p:platform=x64` 
