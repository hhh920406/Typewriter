function [J, grad] = lrCostFunction(theta, X, y, lambda)
    m = length(y);
    h = sigmoid(X * theta);
    t = theta;
    t(1) = 0;
    J = sum(- y .* (log(h)) - (1 - y) .* (log(1 - h))) / m + ...
        lambda / (2 * m) * sum(t .^ 2);
    grad = (X' * (h - y)) / m + lambda / m * t;
end
