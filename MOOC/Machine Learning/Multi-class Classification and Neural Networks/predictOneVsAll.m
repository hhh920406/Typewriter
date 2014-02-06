function p = predictOneVsAll(all_theta, X)
    X = [ones(size(X, 1), 1), X];
    [v, p] = max(X * all_theta', [], 2);
end
