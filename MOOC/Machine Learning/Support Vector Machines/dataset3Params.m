function [C, sigma] = dataset3Params(X, y, Xval, yval)
    choice = [0.01, 0.03, 0.1, 0.3, 1, 3, 10, 30];
    errors = zeros(length(choice));
    for i = 1 : length(choice)
        for j = 1 : length(choice)
            C = choice(i);
            sigma = choice(j)
            model = svmTrain(X, y, C, @(x1, x2)gaussianKernel(x1, x2, sigma));
            predict = svmPredict(model, Xval);
            errors(i, j) = sum(predict != yval);
        end
    end
    minError = min(min(errors));
    [i, j] = find(errors == minError);
    C = choice(i);
    sigma = choice(j);
end
