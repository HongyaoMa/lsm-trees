% Generating large key value datasets
% CS265 Projec
% Hongyao Ma
% 05/06/2016

clear;
clc;
close all;

tic 

num_pairs = 10^8;

keys = randperm(num_pairs)';

vals = randi(10^10, num_pairs, 1);

% csvwrite('data_1Mkeys.csv', [keys, vals]);
dlmwrite('data_100Mpairs.csv',[keys, vals],'delimiter',',','precision',10)

toc