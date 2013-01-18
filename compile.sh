#!/bin/bash

# Load Latest GCC Compliler (compatible with c++11)
. /etc/profile.d/modules.sh
module load modules modules-init modules-gs
module load mpc/0.8.2
module load mpfr/3.1.0
module load gmp/5.0.2
module load gcc/4.7.0

# compile the code
g++ *.cpp -o lcp -std=c++0x

# give the program execution authority
chmod 777 lcp
