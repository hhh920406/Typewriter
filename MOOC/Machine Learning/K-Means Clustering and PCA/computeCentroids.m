function centroids = computeCentroids(X, idx, K)
    [m n] = size(X);
    centroids = zeros(K, n);
    for i = 1 : K
        pos = zeros(1, n);
        num = 0.0;
        for j = 1 : m
            if idx(j) == i
                pos += X(j, :);
                num += 1.0;
            end
        end
        centroids(i, :) = pos / num;
    end
end

