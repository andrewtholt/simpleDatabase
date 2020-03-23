#!/bin/bash

set -x

LD_LIBRARY_PATH=$(pwd)
export LD_LIBRARY_PATH

PATH=$PATH:.

echo "br main" > /tmp/gdb_cmds.txt
echo "info br" >> /tmp/gdb_cmds.txt
echo "run" >> /tmp/gdb_cmds.txt

gdb -x /tmp/gdb_cmds.txt $1
