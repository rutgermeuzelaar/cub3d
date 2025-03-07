#!/bin/bash

tmpdir=$(mktemp -d)
invalid_dir="maps/invalid"
invalid_maps=$(ls $invalid_dir)

for map in $invalid_maps
	do echo $map
	valgrind --suppressions=MLX42.supp --track-fds=yes \
	--leak-check=full --show-leak-kinds=all --track-origins=yes ./cub3D $invalid_dir/$map
	echo
done
