function idx = findClosestCentroids(X, centroids)
    K = size(centroids, 1);
    m = size(X, 1);
    idx = zeros(m, 1);
    for i = 1 : m
        dist = zeros(K, 1);
        for j = 1 : K
            dist(j) = sum((X(i, :) - centroids(j, :)) .^ 2);
        end
        [mini, idx(i)] = min(dist);
    end
end

