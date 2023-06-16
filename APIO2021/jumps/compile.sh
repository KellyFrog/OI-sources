#!/bin/bash

problem=jumps
grader_name=stub

echo g++ -std=gnu++17 -O2 -pipe -o "${problem}.exe" "${grader_name}.cpp" "${problem}.cpp"
g++ -std=gnu++17 -O2 -pipe -o "${problem}.exe" "${grader_name}.cpp" "${problem}.cpp"
