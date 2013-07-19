clear ; close all; clc
input_layer_size  = 400;
num_labels = 10;
%% =========== Part 1: Loading and Visualizing Data =============
fprintf('Loading and Visualizing Data ...\n')
load('ex3data1.mat');
m = size(X, 1);
rand_indices = randperm(m);
sel = X(rand_indices(1:100), :);
displayData(sel);
fprintf('Program paused. Press enter to continue.\n');
pause;

%% ============ Part 2: Vectorize Logistic Regression ============
fprintf('\nTraining One-vs-All Logistic Regression...\n')
lambda = 0.1;
[all_theta] = oneVsAll(X, y, num_labels, lambda);
fprintf('Program paused. Press enter to continue.\n');
pause;

%% ================ Part 3: Predict for One-Vs-All ================
pred = predictOneVsAll(all_theta, X);
fprintf('\nTraining Set Accuracy: %f\n', mean(double(pred == y)) * 100);

