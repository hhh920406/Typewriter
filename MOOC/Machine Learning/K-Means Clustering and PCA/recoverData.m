function X_rec = recoverData(Z, U, K)
    X_rec = Z * U(:, 1 : K)';
end
