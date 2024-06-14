#!/usr/bin/bash

extension=".bak"

for nombre in $(ls)
do
	cp $nombre "$nombre$extension"
done
