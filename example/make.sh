#!/bin/bash

ln -s ../deque.h deque.h
gcc -o test item.c item.h deque.h #2&1| less
chmod +x test