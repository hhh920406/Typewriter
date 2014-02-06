function Z = projectData(X, U, K)
    Z = X * U(:, 1 : K);
end
