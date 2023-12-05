# MPICH installation command

Make sure that the environment variables `CC`, `CXX` and `FC` are set, then

```shell
../configure --prefix=$PWD/../gcc-install \
--enable-shared \
--enable-sharedlibs=$CC \
--enable-fast=O2 \
--enable-debuginfo \
--enable-totalview \
--enable-two-level-namespace \
CC=$CC \
CXX=$CXX \
FC=$FC \
CFLAGS='' \
CXXFLAGS='' \
FFLAGS='-fallow-argument-mismatch' \
FCFLAGS='-fallow-argument-mismatch' \
F90FLAGS='' \
F77FLAGS=''
```