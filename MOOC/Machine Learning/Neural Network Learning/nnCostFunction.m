function [J grad] = nnCostFunction(nn_params, input_layer_size, hidden_layer_size, num_labels, X, y, lambda)
    Theta1 = reshape(nn_params(1:hidden_layer_size * (input_layer_size + 1)), hidden_layer_size, (input_layer_size + 1));
    Theta2 = reshape(nn_params((1 + (hidden_layer_size * (input_layer_size + 1))):end), num_labels, (hidden_layer_size + 1));
    m = size(X, 1);
    A1 = [ones(m, 1), X];
    Z2 = A1 * Theta1';
    A2 = [ones(m, 1), sigmoid(Z2)];
    Z3 = A2 * Theta2';
    H = sigmoid(Z3);
    Y = zeros(m, num_labels);
    for i = 1 : m
        Y(i, y(i)) = 1;
    end
    Jk = zeros(num_labels, 1);
    for k = 1 : num_labels
        Jk(k) = - Y(:,k)' * log(H(:, k)) - (1 - Y(:, k))' * log(1 - H(:, k));
    end
    J = sum(Jk) / m;
    J = J + lambda / (2 * m) * (sum(sum(Theta1(:, 2 : end) .^ 2)) + sum(sum(Theta2(:, 2 : end) .^ 2)));
    
    delta3 = H - Y;
    delta2 = delta3 * Theta2 .* (A2 .* (1 - A2));
    delta2 = delta2(:, 2 : end);
    Delta2 = zeros(size(delta3, 2), size(A2, 2));
    Delta1 = zeros(size(delta2, 2), size(A1, 2));
    for i = 1 : m
        Delta2 = Delta2 + delta3(i, :)' * A2(i, :);
        Delta1 = Delta1 + delta2(i, :)' * A1(i, :);
    end
    Theta1_grad = Delta1 / m;
    Theta2_grad = Delta2 / m;
    Theta1_grad(:, 2 : end) = Theta1_grad(:, 2 : end) + Theta1(:, 2 : end) * lambda / m;
    Theta2_grad(:, 2 : end) = Theta2_grad(:, 2 : end) + Theta2(:, 2 : end) * lambda / m;
    grad = [Theta1_grad(:) ; Theta2_grad(:)];
end
