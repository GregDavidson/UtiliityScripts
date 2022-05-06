#!/bin/sh
find . -type f -print | while read f; do g=$(echo $f | tr ' ' '_'); [ "$f" != "$g" ] && mv "$f" "$g"; done
