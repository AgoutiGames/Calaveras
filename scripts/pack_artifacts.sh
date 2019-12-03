#!/bin/bash
set -e
usage="Usage: ./pack_artifacts.sh [PLATFORM] [BIT] [LIBRARY] [VERSION]
PLATFORM: \"linux\", \"windows\"
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

if [ "$P" != "linux" ] && [ "$P" != "windows" ]
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
#PROJECT_NAME=${PWD##*/}
PROJECT_NAME="Calaveras"
if [ "$P" = "linux" ]
then
    mkdir libs
    cp build/salmon/libSalmon.so libs/
    tar cfvz ./${PROJECT_NAME}-${TRAVIS_TAG}-${P}${B}.tar.gz bin libs data -C ./scripts startGame.sh -C ../salmon/scripts fetch_dependencies.sh
    rm -r libs
elif [ "$P" = "windows" ]
then
    cp ./salmon/dependencies/win${B}/lib/*.dll ./bin
    cp ./build/salmon/libSalmon.dll ./bin
    zip -r ./${PROJECT_NAME}-${TRAVIS_TAG}-${P}${B}.zip ./bin ./data
else
    echo "Please define env var \"PLATFORM\" eiter with \"linux\" or \"windows\""
    exit 1
fi
rm -r bin
echo "Successfully packed artifacts at root level"