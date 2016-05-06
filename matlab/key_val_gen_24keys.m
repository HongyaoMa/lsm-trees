% Data generation for the CS 265 class project
% Hongyao Ma
% 05/05/2016

clear;
clc;
close all;

num_pairs = 32;

keys = randperm(num_pairs)'

vals = randi(10^9, num_pairs, 1)

dlmwrite('data_32pairs_largeKeys.csv',[keys, vals],'delimiter',',','precision',9)

%csvwrite('data_32pairs_largeKeys.csv', [keys, vals])

