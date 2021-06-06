#!/bin/bash

problem=jumps
grader_name=stub

g++ -std=gnu++17 -g -pipe -o "${problem}" "${grader_name}.cpp" "${problem}.cpp"
