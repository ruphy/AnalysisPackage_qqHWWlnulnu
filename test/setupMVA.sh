#!/bin/sh

# set symbolic links to data file and to rootmaps
#cd test;
if [ ! -h libTMVA.rootmap ]; then ln -s /home/andrea/tmva-V04-01-00/lib/libTMVA.rootmap; fi
if [ ! -h .rootmap ]; then ln -s /home/andrea/tmva-V04-01-00/lib/libTMVA.rootmap .rootmap; fi

# Check Root environment setup
# It's checked in such a fancy way, because if you install ROOT using
# Fink on Mac OS X, thet will not setup the ROOTSYS environment variable.
# (The layout of ROOT is a bit different in that case...)
#if test ! "$ROOTSYS" -a ! -e `which root-config`; then
#if [[ ! $ROOTSYS && ! -e `which root-config` ]]; then  ### not shell conform (shell on lxplus is bash, don't test there)
if [ ! $ROOTSYS ]; then
    echo "ERROR: Root environment not yet defined."
    echo "Please do so by setting the ROOTSYS environment variable to the"
    echo "directory of your root installation or to ROOT on CERN-afs (see http://root.cern.ch)! "
    return 1
fi

# On MacOS X $DYLD_LIBRARY_PATH has to be modified, so:
if [[ `root-config --platform` == "macosx" ]]; then

    if [ ! $DYLD_LIBRARY_PATH ]; then
        export DYLD_LIBRARY_PATH=/home/andrea/tmva-V04-01-00/lib:`root-config --libdir`
    else
        export DYLD_LIBRARY_PATH=/home/andrea/tmva-V04-01-00/lib:${DYLD_LIBRARY_PATH}
    fi

elif [[ `root-config --platform` == "solaris" ]]; then

    if [ ! $LD_LIBRARY_PATH ]; then
        export LD_LIBRARY_PATH=/home/andrea/tmva-V04-01-00/lib:`root-config --libdir`
    else
        export LD_LIBRARY_PATH=/home/andrea/tmva-V04-01-00/lib:${LD_LIBRARY_PATH}
    fi

else
    grep -q `echo $ROOTSYS/lib` /etc/ld.so.cache
    root_in_ld=$?
    if [ ! $LD_LIBRARY_PATH ]; then
        if [ $root_in_ld -ne 0 ]; then
            echo "Warning: so far you haven't setup your ROOT enviroment properly (no LD_LIBRARY_PATH): TMVA will not work"
        fi
    fi
    export LD_LIBRARY_PATH=/home/andrea/tmva-V04-01-00/lib:${LD_LIBRARY_PATH}

fi

# prepare for PyROOT
export PYTHONPATH=/home/andrea/tmva-V04-01-00/lib:`root-config --libdir`:$PYTHONPATH

