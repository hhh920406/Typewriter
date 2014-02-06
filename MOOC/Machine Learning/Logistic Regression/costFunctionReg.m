function [J, grad] = costFunctionReg(theta, X, y, lambda)
    m = length(y);
    n = length(theta);
    h = sigmoid(X * theta);
    theta(1) = 0;
    J = sum((- y .* log(h) - (ones(m, 1) - y) .* log(ones(m, 1) - h))) / m + lambda / (2 * m) * sum(theta .^ 2);
    grad = (X' * (h - y)) / m + lambda / m * theta;
end
