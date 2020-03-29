#!/bin/bash
set -e
cd "$(dirname "${BASH_SOURCE[0]}")"
if [ -d "../emsdk" ] 
then
    echo "Emscripten already fetched!" 
else
    cd ../
    git clone https://github.com/emscripten-core/emsdk.git
    cd emsdk
    git pull
    ./emsdk install latest
    ./emsdk activate latest
    echo "Fetched Emscripten successfully"
fi
