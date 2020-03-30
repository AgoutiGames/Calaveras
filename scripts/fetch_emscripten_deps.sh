#!/bin/bash
set -e
cd "$(dirname "${BASH_SOURCE[0]}")"
if [ -d "../emscripten_deps" ] 
then
    echo "Emscripten dependencies already fetched!" 
else
    cd ../
    
    # Make emcc available for terminal
    source ./emsdk/emsdk_env.sh 
    
    mkdir emscripten_deps
    cd emscripten_deps
    mkdir lib
    mkdir include
    
    # Fetch b64
    git clone https://github.com/libb64/libb64
    cd libb64/src
    emmake make
    
    cp libb64.a ../../lib
    cp -r ../include ../../
    echo "Fetched b64"
    
    # Fetch tinyxml2
    cd ../../
    
    git clone https://github.com/leethomason/tinyxml2.git
    cd tinyxml2
    git checkout tags/7.1.0
    mkdir build
    cd build
    emcmake cmake -DCMAKE_BUILD_TYPE="Release" -DBUILD_SHARED_LIBS:BOOL=OFF -DBUILD_STATIC_LIBS:BOOL=ON -DBUILD_TESTS:BOOL=OFF ..
    emmake make

    cp libtinyxml2.a ../../lib
    cp ../tinyxml2.h ../../include

    echo "Fetched Emscripten dependencies successfully"
fi
