CG1
=====


```
git submodule update  --init --recursive
mkdir bin
cd bin
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --config Release
ctest --config Release
```

```
git clone https://github.com/spurious/SDL-mirror.git
cd SDL-mirror/
git checkout release-2.0.9
mkdir bin
cd bin
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --config Release
cmake -DCMAKE_INSTALL_PREFIX=/c/Users/markus/Documents/SDL2 -P cmake_install.cmake
```

```
git clone https://github.com/Perlmint/glew-cmake.git
cd glew-cmake/
git checkout glew-2.1.0
mkdir bin
cd bin
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --config Release
```

```
 -DCMAKE_PREFIX_PATH=/c/Users/markus/glew-2.1.0/include 
 -DCMAKE_PREFIX_PATH=/c/Users/markus/glew-2.1.0/lib/Release/x64/
```

