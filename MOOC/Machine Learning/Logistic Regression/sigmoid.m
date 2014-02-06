function g = sigmoid(z)
    g = 1 ./ (ones(size(z)) + exp(-z));
end
