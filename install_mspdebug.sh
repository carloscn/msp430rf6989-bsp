# !/bin/bash

function utils_check_ret()
{
	if [ $1 -eq 0 ]; then
        echo "[INFO] $2 done!"
    else
        echo "[ERR] Failed on $2!"
        exit -1
    fi
}

BRANCH=v0.25
if [[ "$UNAME_STR" == "Linux" ]]; then
    echo "Linux OS"
    sudo apt-get install libreadline-dev
    git clone git@github.com:dlbeer/mspdebug.git --depth=1 -b ${BRANCH}
    pushd mspdebug
    make -j8 && sudo make install
    popd
elif [[ "$UNAME_STR" == *"MINGW"* || "$UNAME_STR" == *"CYGWIN"* ]]; then
    echo "Windows OS"
elif [[ "$UNAME_STR" == "Darwin" ]]; then
    echo "MAC OS"
else
    echo "Unsupported OS: $UNAME_STR"
    exit 1
fi

mspdebug --help