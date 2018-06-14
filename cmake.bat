rm -rf build
md build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -G "NMake Makefiles" ..
nmake
cd ..