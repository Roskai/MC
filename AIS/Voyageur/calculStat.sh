#!/bin/bash

i=0

while [ $i -le $1 ]
do
  ./ais 1000 50 20 1000 30 
  ((i++))
done