#!/bin/bash

# input
if [ "$#" -ne 1 ]; then
	echo
	echo "Usage:"
    echo "        $0  2D?"
	echo
	exit 1
fi

# generate f90 file
IN=hmat3d.f90
OUT=hmat3d.go
if [ "$1" -gt 0 ]; then # 2D
    ./hmat 1 | maxima
    IN=hmat2d.f90
    OUT=hmat2d.go
else
    ./hmat | maxima
fi

# join lines
source "join_f90_lines.bash" $IN $OUT

# replace sqrt(2) with math.Sqrt2, 2* with 2.0*, and '+' with ' + '
sed -i -e 's/sqrt(2)/math.Sqrt2/g' \
       -e 's/\<2\*/2.0\*/g'        \
       -e 's/+/ + /g'              \
       -e 's/\/2.0/ \/ 2.0/g'      $OUT

# replace k## with o.κ[#][#]
for i in 0 1 2; do
    for j in 0 1 2; do
        sed -i -e "s/k$i$j/o.κ[$i][$j]/g" $OUT
    done
done

# replace Gm# with o.g.G[m][#] and Gn# with o.g.G[n][#]
for i in 0 1 2; do
    sed -i -e "s/Gm$i/o.g.G[m][$i]/g" \
           -e "s/Gn$i/o.g.G[n][$i]/g" $OUT
done

# replace Hmn with o.H[m][n]
sed -i -e "s/Hmn/o.H[m][n]/g" $OUT

# remove input file
rm $IN
