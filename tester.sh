#!/bin/bash

tmpdir=$(mktemp -d)
invalid_dir="maps/invalid"
invalid_maps=$(ls $invalid_dir)

for map in $invalid_maps
	do echo $map
	./cub3D $invalid_dir/$map
	echo
done
