#! /bin/bash

echo "Enter first number \n"
read a
echo "Enter second number \n"
read b
echo "Enter third number \n"
read c

if [ $a -gt  $b ]
then
	if [ $a -gt $c ]
	then
		echo "$a is greatest \n"
	else
		if [ $c -gt $b ]
		then
			echo "$c is greatest \n"
		else 
			echo "$b is greatest \n"
		fi
	fi
else
	if [ $b -gt $c ]
	then
		echo "$b is greatest \n"
	else
		echo "$c is greatest \n"
	fi
fi
