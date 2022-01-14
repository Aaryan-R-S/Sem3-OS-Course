#! /bin/bash

if test $# -ne 3
then 
    echo "Invalid arguments!"
    echo "Follow the given format:"
    echo "./cal.sh dd mm yyyy"
else
    if test $3 -lt 1
    then
        echo "Invalid Year!"
    elif test $2 -lt 1 -o  $2 -gt 12
    then
        echo "Invalid Month!"
    else
        a=`cal $2 $3 |egrep -v [a-z] |wc -w`
        if test $1 -lt 1 -o  $1 -gt $a
        then
            echo "Invalid Date!"
        else
            cal $2 $3
        fi
    fi
fi