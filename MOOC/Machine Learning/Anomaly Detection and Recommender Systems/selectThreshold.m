function [bestepsilon bestf1] = selectThreshold(yval, pval)
    bestepsilon = 0;
    bestf1 = 0;
    f1 = 0;
    stepsize = (max(pval) - min(pval)) / 1000;
    for epsilon = min(pval):stepsize:max(pval)
        predict = (pval < epsilon);
        tp = sum((predict == 1) & (yval == 1));
        fp = sum((predict == 1) & (yval == 0));
        fn = sum((predict == 0) & (yval == 1));
        precise = tp / (tp + fp);
        recall = tp / (tp + fn);
        f1 = 2 * precise * recall / (precise + recall);
        if f1 > bestf1
            bestf1 = f1;
            bestepsilon = epsilon;
        end
    end
end

