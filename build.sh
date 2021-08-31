#!/bin/bash

pwd_dir=`pwd`
echo "${pwd_dir}"

g++ $@ ${pwd_dir}/../../glad/src/glad.c -o test -lGL -lGLEW -lglfw -ldl
