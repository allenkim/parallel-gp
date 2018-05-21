#!/bin/bash
counter=1
while [ $counter -le 24 ]
	do
		./main $counter >> scalability.txt
		((counter++))
		done
