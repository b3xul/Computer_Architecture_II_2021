#!/bin/bash
#these paths must point to the installed gem5 folders
export PYTHONPATH=$PYTHONPATH:/home/gem5/gem5
export PYTHONPATH=$PYTHONPATH:/home/gem5/gem5/configs/common
export PYTHONPATH=$PYTHONPATH:/home/gem5/gem5/configs
export PYTHONPATH=$PYTHONPATH:/home/gem5/gem5/src/python
export PYTHONPATH=$PYTHONPATH:/home/gem5/gem5/src/python/m5
export PYTHONPATH=$PYTHONPATH:/home/gem5/gem5/src/sim



# ------- Add to PATH the build model ---------
export PATH=$PATH:/home/gem5/gem5/build/ALPHA/
alias gem5_sim='gem5.opt'
GEM5_DEFAULT_PY='/home/gem5/gem5/configs/example/se.py'

# ------- Compiler paths --------
export PATH=$PATH:/home/gem5/alpha/alphaev67-unknown-linux-gnu/bin/
alias gem5_alpha_compiler='alphaev67-unknown-linux-gnu-gcc'


echo "Setting up environment ... "


