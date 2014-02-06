function g = sigmoidGradient(z)
    s = sigmoid(z);
    g = s .* (1 - s);
end
