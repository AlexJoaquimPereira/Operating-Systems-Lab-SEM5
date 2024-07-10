#! /bin/bash

echo "1. Circle"
echo "2. Triangle"
echo "3. Rectangle"
read choice

case $choice in
	1) echo "Enter the radius"
	read rad
	echo "Area is $((3 * rad * rad))"
	;;
	2) echo "Enter the base and height"
	read base
	read height
	echo "Area is $(((base * height) / 2))"
	;;
	3) echo "Enter the length and breadth"
	read length
	read breadth
	echo "Area is $((length * breadth))"
	;;
	*) echo "Invalid option."
	;;
esac


