#! /bin/bash

echo "Enter two numbers: "
read a
read b

result=$(($a + $b))
echo "Sum of $a and $b is $result"

result=`expr $a - $b`
echo "Difference of $a and $b is $result"

result=`expr $a \* $b`
echo "Product of $a and $b is $result"

result=`expr $a \/ $b`
echo "Quotient of $a and $b is $result"
