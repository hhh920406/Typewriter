function [J, grad] = costFunction(theta, X, y)
    m = length(y);
    h = sigmoid(X * theta);
    J = sum((- y .* log(h) - (ones(m, 1) - y) .* log(ones(m, 1) - h))) / m;
    grad = (X' * (h - y)) / m;
end
