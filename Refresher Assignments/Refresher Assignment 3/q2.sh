#! /bin/bash

if test $# -eq 0 -o $# -eq 1 -o $# -eq 2
then 
    echo "Invalid arguments!"
    echo "Follow the given format:"
    echo "./func.sh operation operand1 operand2 (and more operands)"

elif [ "$1" == "add" ]
then
    argc=$#
    argv=("$@")
    ans=$2
    for (( j=2; j<argc; j++ ))
    do
        ans=$(($ans + ${argv[j]}))
    done
    echo $ans
    
elif [ "$1" == "sub" ]
then
    argc=$#
    argv=("$@")
    ans=$2
    for (( j=2; j<argc; j++ ))
    do
        ans=$(($ans - ${argv[j]}))
    done
    echo $ans
    
elif [ "$1" == "mul" ]
then
    argc=$#
    argv=("$@")
    ans=$2
    for (( j=2; j<argc; j++ ))
    do
        ans=$(($ans * ${argv[j]}))
    done
    echo $ans
    
elif [ "$1" == "div" ]
then
    argc=$#
    argv=("$@")
    ans=$2
    for (( j=2; j<argc; j++ ))
    do
        ans=$(($ans / ${argv[j]}))
    done
    echo $ans
    
elif [ "$1" == "exp" ]
then
    argc=$#
    argv=("$@")
    ans=${argv[$#-1]}
    for (( j=argc-2; j>=1; j-- ))
    do
        ans=$((${argv[j]} ** $ans))
    done
    echo $ans

else
    echo "Invalid operation -- use 'add', 'sub', 'mul', 'div' or 'exp' only"
fi