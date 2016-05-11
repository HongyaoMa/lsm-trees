% Generating large key value datasets
% CS265 Projec
% Hongyao Ma
% 05/06/2016

clear;
clc;
close all;

tic 

num_pairs = 5*10^7;

total_size = 10^9;

keys = randperm(total_size, num_pairs)';

vals = randi(10^10, num_pairs, 1);

toc

% csvwrite('data_1Mkeys.csv', [keys, vals]);
dlmwrite('test_50Moutof1B.csv',[keys, vals],'delimiter',',','precision',10)

toc
