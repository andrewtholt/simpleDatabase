#!/bin/bash

set -x

LD_LIBRARY_PATH=$(pwd)
export LD_LIBRARY_PATH

PATH=$PATH:.

gdb $1
