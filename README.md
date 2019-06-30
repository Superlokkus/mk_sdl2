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
 -DCMAKE_PREFIX_PATH=/c/Users/markus/glew-2.1.0/include 
 -DCMAKE_PREFIX_PATH=/c/Users/markus/glew-2.1.0/lib/Release/x64/
```

