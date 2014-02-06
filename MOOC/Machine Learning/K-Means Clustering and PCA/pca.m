function [U, S] = pca(X)
    [m, n] = size(X);
    Sigma = X' * X / m;
    [U, S, V] = svd(Sigma);
end
