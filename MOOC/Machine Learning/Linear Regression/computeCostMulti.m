function J = computeCostMulti(X, y, theta)
    m = length(y);
    J = (X * theta - y)' * (X * theta - y) / (2 * m);
end
