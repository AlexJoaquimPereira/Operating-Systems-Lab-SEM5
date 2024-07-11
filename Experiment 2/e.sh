#! /bin/bash

smallest=10
largest=0
second_largest=0
second_smallest=10

echo "Enter a number:"
read num

while [ $num -gt 0 ]
do
	x=$(($num % 10))
	if [ $x -gt $largest ];
	then
    	second_largest=$largest
    	largest=$x
  	elif [ $x -gt $second_largest ];
	then
    	second_largest=$x
  	fi
  	if [ $x -lt $smallest ];
	then
    	second_smallest=$smallest
    	smallest=$x
  	elif [ $x -lt $second_smallest ];
	then
    	second_smallest=$x
  	fi
  	num=$(($num / 10))
done

echo "Second largest digit is $second_largest"
echo "Second smallest digit is $second_smallest"