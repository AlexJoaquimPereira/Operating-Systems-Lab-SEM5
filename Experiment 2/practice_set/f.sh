#! /bin/bash

ch=1

while [ $ch -eq 1 ]
do
	echo "1. Display Calendar"
	echo "2. Display user"
	echo "3. Display current working directory"
	read choice
	
	case $choice in
	1) cal
	;;
	2) who
	;;
	3) pwd
	;;
	*) echo "Invalid choice"
	esac
	
	echo "Enter 1 to continue, 0 to exit"
	read ch
	
done
