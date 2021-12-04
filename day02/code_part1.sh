#!/bin/bash
input="data.txt"

fw=$(grep forward $input |  awk '{s+=$2} END {print s}')
down=$(grep down $input |  awk '{s+=$2} END {print s}')
up=$(grep up $input |  awk '{s+=$2} END {print s}')
echo "$fw $up $down"
echo $(( fw * (down - up) ))