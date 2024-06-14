#!/bin/bash

filename="textillo.txt"

if [ -f $filename ]
then
	echo "Es fichero"
elif [ -d $filename ]
then
	echo "Es directorio"
else
	echo "No es fichero"
fi
