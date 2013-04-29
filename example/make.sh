#!/bin/bash

rm deque.h
ln -s ../deque.h deque.h
gcc -o test deque.h item.h item.c #2&1| less
chmod +x test