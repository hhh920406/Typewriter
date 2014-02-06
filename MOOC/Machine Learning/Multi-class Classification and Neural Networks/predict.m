function p = predict(Theta1, Theta2, X)
    X1 = sigmoid([ones(size(X), 1), X] * Theta1');
    X2 = sigmoid([ones(size(X1), 1), X1] * Theta2');
    [v, p] = max(X2, [], 2);
end
