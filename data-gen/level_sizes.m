% Compute sizes of each level
% The CS 265 Project

% Hongyao Ma
% 05/06/2016

clear;
clc;
close all;

keys = 32;
vals = 64;
c0 = 100000;
max_level = 12;

level0 = c0 *(keys + vals) /8/1024/1024

size_of_each_level = level0*(2.^[1:max_level])

max_size_up_to_level = cumsum(size_of_each_level)

total_size = max_size_up_to_level(end)

total_number = total_size*1024*1024*8 / (keys + vals)

block_sizes = c0 * 2.^[0:max_level-1]

nums100M = [2 1 1 2 1 2 2 2 2 0 0 0];

total100M = sum(nums100M.* block_sizes) + 0



