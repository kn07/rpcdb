#!/bin/bash

./compile.sh
./build/server &

for i in $(find ./tests -name '*.txt')
do
    ./build/client localhost $i
done

kill -9 $(pidof server)
rm *.rpcdb
