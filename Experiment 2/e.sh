#! /bin/bash

smallest=10
largest=0

echo "Enter a number:"
read num

while [ $num -gt 0 ]
do
	x=$(($num % 10))
	if [ $x -gt $largest ];
	then
		largest=$x
	fi
	if [ $x -lt $smallest ];
	then
		smallest=$x
	fi
	num=$(($num / 10))
done

echo "Largest digit is $largest"
echo "Smallest digit is $smallest"