#! /bin/bash
echo "Hello, world!"

: '
multiline
comment'


# save output to another file
# echo "Hello, world, in bash!" > a.txt

# save input to another file and thus overwrite it
# cat > a.txt

# append input to another file
# cat >> a.txt



# age=28
# # lt, eq, ne, gt for relational operators
# if [ $age -lt 11 ]
# then
#     echo "T"
# elif [ $age -eq 100 ]
# then 
#     echo "U"
# else
#     echo "F"
# fi



# -o, -a for 'or' and 'and' operator
# if [ $age -eq 18 -o $age -eq 28 ]
# then 
#     echo "Special"
# else
#     echo "Oops"
# fi



# age=4
# while [ $age -lt 10 ]
# do
#     echo $age
#     age=$((age+1))
# done




# for i in {0..20..2}
# do
#     echo $i
# done


# for i in {0..20..2}
# do
#     if [ $i -eq 14 ]
#     then 
#         break
#     elif [ $i -lt 10 ]
#     then
#         continue
#     fi
#     echo $i
# done

# Inputs -- give them in terminal just after the name of the file
# echo $1 $2 $3

# infinite inputs
# args=("$@")   
# echo ${args[0]} ${args[1]}
# echo $@


# Strings
# echo "a1"
# read a1
# echo "b1"
# read b1
# if [ $a1 == $b1 ]
# then 
#     echo "Ok"
# else
#     echo "No"
# fi


# Numbers and Arithmetics
# n1=4
# n2=20
# echo $(( $n1 + $n2 ))
# echo $(( $n1 - $n2 ))
# echo $(( $n1 / $n2 ))
# echo $(( $n1 * $n2 ))
# echo $(( $n1 % $n2 ))


# # Arrays
# car=('madf' 'fvws' 'WEf')
# echo "${car[@]}" 
# echo "${car[1]}" 
# echo "${!car[@]}"   # index
# echo "${#car[@]}"   # total values


# # Functions
# function f1()
# {
#     echo $1 $2
# }

# f1 hi hello

echo "Ok"