#!/bin/bash

# Load Latest GCC Compliler (compatible with c++11)
. /etc/profile.d/modules.sh
module load modules modules-init modules-gs
module load mpc/0.8.2
module load mpfr/3.1.0
module load gmp/5.0.2
module load gcc/4.7.0

# run the script
./lcp NC_007205.fna NC_012920.fna