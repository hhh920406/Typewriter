function [X_norm, mu, sigma] = featureNormalize(X)
    mu = mean(X);
    sigma = std(X);
    X_norm = (X - ones(size(X, 1), 1) * mu) ./ (ones(size(X, 1), 1) * sigma);
end
