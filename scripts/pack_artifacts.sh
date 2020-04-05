#!/bin/bash
set -e
usage="Usage: ./pack_artifacts.sh [PLATFORM] [BIT] [VERSION]
PLATFORM: \"linux\", \"windows\" \"web\"
BIT: \"64\", \"32\"
VERSION: any string"
if [ "$1" ==  "--help" ] || [ "$1" == "-h" ]
then
    echo "$usage"
    exit
fi

if [ "$1" ]
then
    P=$1
else
    P=$PLATFORM
fi

if [ "$2" ]
then
    B=$2
else
    B=$BIT
fi

if [ "$3" ]
then
    TRAVIS_TAG=$4
fi

if [ "$P" != "linux" ] && [ "$P" != "windows" ] && [ "$P" != "web" ]
then
    echo "PLATFORM parameter or env var is not properly set! Value is: \"${P}\"!"
    echo "Please check help page via \"./pack_artifacts -h\""
    exit 1
fi
if [ "$B" != "64" ] && [ "$B" != "32" ]
then
    echo "BIT parameter or env var is not properly set! Value is: \"${B}\"!"
    echo "Please check help page via \"./pack_artifacts -h\""
    exit 1
fi

cd "$(dirname "${BASH_SOURCE[0]}")"
cd ../
# Either set project name manually or to directory name
PROJECT_NAME=${PWD##*/}
#PROJECT_NAME="Game"
if [ "$P" == "linux" ]
then
    mkdir libs
    cp lib/libSalmon.so libs/
    cp salmon/LICENSE libs/LICENSE.libSalmon.txt
    cp LICENSE bin/LICENSE.${PROJECT_NAME}.txt 
    tar cfvz ./${PROJECT_NAME}-${TRAVIS_TAG}-${P}${B}.tar.gz bin libs data -C ./salmon/scripts fetch_dependencies.sh
    rm -r bin
    rm -r libs
elif [ "$P" == "windows" ]
then
    cp ./salmon/dependencies/win${B}/lib/*.dll ./bin
    cp ./salmon/dependencies/win${B}/lib/*.txt ./bin
    cp ./lib/libSalmon.dll ./bin
    cp salmon/LICENSE bin/LICENSE.libSalmon.txt
    cp LICENSE bin/LICENSE.${PROJECT_NAME}.txt 
    zip -r ./${PROJECT_NAME}-${TRAVIS_TAG}-${P}${B}.zip ./bin ./data
    rm -r bin
elif [ "$P" == "web" ]
then
    cd build
    mv *.html index.html
    zip -r ./${PROJECT_NAME}-${TRAVIS_TAG}-${P}.zip *.html *.js *.wasm *.data
    mv *.zip ../
else
    echo "Please define env var \"PLATFORM\" eiter with \"linux\", \"windows\" or \"web\""
    exit 1
fi
echo "Successfully packed artifacts at root level"
