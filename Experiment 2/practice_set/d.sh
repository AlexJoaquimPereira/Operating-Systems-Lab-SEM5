#! /bin/bash

echo "Enter year"
read year

if [ `expr $year % 4` - eq 0 ]
then
	echo "$year is a leap year"
else
	echo "$echo is not a leap year"
fi
