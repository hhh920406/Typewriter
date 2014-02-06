f = [0.5; 0.9; 0.1; 0.6; 0.4];
nut = [53 40 12 53 6; 4.4 8 3 12 1.9; 0.4 3.6 2 0.9 0.3];
A = [nut;-nut];
maxN = [1000; 100; 100];
minN = [100; 10; 0];
b = [maxN;-minN];
Sol = linprog(f, A, b, [], [], zeros(1, 5));
res = f' * Sol;

kind = [0.2 -0.54 -0.06 -0.36 -0.24;
    -0.3 0.36 -0.06 -0.36 -0.24;
    -0.3 -0.54 0.04 -0.36 -0.24;
    -0.3 -0.54 -0.06 0.24 -0.24;
    -0.3 -0.54 -0.06 -0.36 0.16];
A = [nut;-nut;kind];
kindB = [0; 0; 0; 0; 0];
b = [maxN;-minN;kindB];
Sol = linprog(f, A, b, [], [], zeros(1, 5));
res = f' * Sol;

f = [4.4; 8; 3; 12; 1.9];
money = [0.5, 0.9, 0.1, 0.6, 0.4];
moneyB = [2];
A = [nut;-nut;money];
b = [maxN;-minN;moneyB];
Sol = linprog(-f, A, b, [], [], zeros(1, 5));
res = f' * Sol;