function x = emailFeatures(word_indices)
    n = 1899;
    x = zeros(n, 1);
    x(word_indices) = 1;
end
