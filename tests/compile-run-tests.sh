#!/bin/bash

if [ -z "$1" ]; then
    echo "Usage: $0 <target_name>"
    exit 1
fi

make TEST_FILE=$1.c
./$1
