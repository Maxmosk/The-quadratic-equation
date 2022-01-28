#!/bin/sh
while IFS=% read -r source roots; do
        res=$(echo $source | ./quad)
        res=$(echo "$res" | tail -n +2)
        if [ x"$roots" != x"$res" ]; then
                echo TEST $source FAILED: expexted "$roots", got "$res"
        fi
done <<END
        1 2 1%-1.000
        1 4 3%-3.000 -1.000
        1 2 f%Incorrect input
END

