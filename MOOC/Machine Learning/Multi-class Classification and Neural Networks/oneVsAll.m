function [all_theta] = oneVsAll(X, y, num_labels, lambda)
    m = size(X, 1);
    n = size(X, 2);
    X = [ones(m, 1), X];
    options = optimset('GradObj', 'on', 'MaxIter', 50);
    initial_theta = zeros(n + 1,1);
    for c = 1 : num_labels
        all_theta(c, :)= fmincg (@(t)(lrCostFunction(t, X,(y == c), lambda)), initial_theta, options);
    end
end
