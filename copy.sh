#!/bin/bash

if ! command -v xclip &> /dev/null; then
	echo "xclip is not installed. Please install it first."
	exit 1
fi


if [ $# -ne 1 ]; then
	echo "Usage: $0 <filename>"
	exit 1
fi


file_to_copy = "$1"


if [ ! -f "$file_to_copy" ]; then
	echo "File not found: $file_to_copy"
	exit 1
fi

cat "$file_to_copy" | xclip -selection clipboard

echo "Contents of $file_to_copy copied to the clipboard."
