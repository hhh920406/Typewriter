function [theta] = normalEqn(X, y)
    theta = inv(X' * X) * X' * y;
end
