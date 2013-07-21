function [J, grad] = linearRegCostFunction(X, y, theta, lambda)
    m = length(y);
    h = X * theta;
    J = sum((h - y) .^ 2) / (2 * m) + lambda / (2 * m) * sum(theta(2 : end) .^ 2);
    theta(1) = 0;
    grad = X' * (h - y) / m + lambda / m * theta;
end
