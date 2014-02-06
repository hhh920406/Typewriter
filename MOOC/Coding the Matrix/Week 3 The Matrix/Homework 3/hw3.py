from mat import Mat
from vec import Vec
from matutil import *

## Problem 1
vector_matrix_product_1 = [1, 0]
vector_matrix_product_2 = [0, 4.44]
vector_matrix_product_3 = [14, 20, 26]

## Problem 2
M_swap_two_vector = [[0, 1], [1, 0]]

## Problem 3
three_by_three_matrix = [[1, 0, 1], [0, 1, 0], [1, 0, 0]] 

## Problem 4
multiplied_matrix = [[2, 0, 0], [0, 4, 0], [0, 0, 3]]

## Problem 5
part_1_valid = False
part_1_number_rows = None
part_1_number_cols = None

part_2_valid = False
part_2_number_rows = None
part_2_number_cols = None

part_3_valid = True
part_3_number_rows = 1
part_3_number_cols = 2

part_4_valid = True
part_4_number_rows = 2
part_4_number_cols = 1

part_5_valid = False
part_5_number_rows = None
part_5_number_cols = None

part_6_valid = True
part_6_number_rows = 1
part_6_number_cols = 1

part_7_valid = True
part_7_number_rows = 3
part_7_number_cols = 3

## Problem 6
small_mat_mult_1 = [[8, 13], [8, 14]]
small_mat_mult_2 = [[24, 11, 4], [1, 3, 0]]
small_mat_mult_3 = [[3, 13]]
small_mat_mult_4 = [[14]]
small_mat_mult_5 = [[1, 2, 3], [2, 4, 6], [3, 6, 9]]
small_mat_mult_6 = [[-2, 4], [1, 1], [1, -3]]

## Problem 7
part_1_AB = [[5, 2, 0, 1], [2, 1, -4, 6], [2, 3, 0, -4], [-2, 3, 4, 0]]
part_1_BA = [[1, -4, 6, 2], [3, 0, -4, 2], [3, 4, 0, -2], [2, 0, 1, 5]]

part_2_AB = [[5, 1, 0, 2], [2, 6, -4, 1], [2, -4, 0, 3], [-2, 0, 4, 3]]
part_2_BA = [[3, 4, 0, -2], [3, 0, -4, 2], [1, -4, 6, 2], [2, 0, 1, 5]]

part_3_AB = [[1, 0, 5, 2], [6, -4, 2, 1], [-4, 0, 2, 3], [0, 4, -2, 3]]
part_3_BA = [[3, 4, 0, -2], [1, -4, 6, 2], [2, 0, 1, 5], [3, 0, -4, 2]]

## Problem 8
matrix_matrix_mult_1    = [[1, 'a+b'], [0, 1]]
matrix_matrix_mult_2_A2 = [[1, 2], [0, 1]]
matrix_matrix_mult_2_A3 = [[1, 3], [0, 1]]
matrix_matrix_mult_2_An = [[1, 'n'], [0, 1]]

## Problem 9
your_answer_a_AB = [[0, 0, 2, 0], [0, 0, 5, 0], [0, 0, 4, 0], [0, 0, 6, 0]]
your_answer_a_BA = [[0, 0, 0, 0], [4, 4, 4, 0], [0, 0, 0, 0], [0, 0, 0, 0]]

your_answer_b_AB = [[0, 2, -1, 0], [0, 5, 3, 0], [0, 4, 0, 0], [0, 6, -5, 0]]
your_answer_b_BA = [[0, 0, 0, 0], [1, 5, -2, 3], [0, 0, 0, 0], [4, 4, 4, 0]]

your_answer_c_AB = [[6, 0, 0, 0], [6, 0, 0, 0], [8, 0, 0, 0], [5, 0, 0, 0]]
your_answer_c_BA = [[4, 2, 1, -1], [4, 2, 1, -1], [0, 0, 0, 0], [0, 0, 0, 0]]

your_answer_d_AB = [[0, 3, 0, 4], [0, 4, 0, 1], [0, 4, 0, 4], [0, -6, 0, -1]]
your_answer_d_BA = [[0, 11, 0, -2], [0, 0, 0, 0], [0, 0, 0, 0], [1, 5, -2, 3]]

your_answer_e_AB = [[0, 3, 0, 8], [0, -9, 0, 2], [0, 0, 0, 8], [0, 15, 0, -2]]
your_answer_e_BA = [[-2, 12, 4, -10], [0, 0, 0, 0], [0, 0, 0, 0], [-3, -15, 6, -9]]

your_answer_f_AB = [[-4, 4, 2, -3], [-1, 10, -4, 9], [-4, 8, 8, 0], [1, 12, 4, -15]]
your_answer_f_BA = [[-4, -2, -1, 1], [2, 10, -4, 6], [8, 8, 8, 0], [-3, 18, 6, -15]]

## Problem 10
column_row_vector_multiplication1 = Vec({0, 1}, {0:13, 1:20})
column_row_vector_multiplication2 = Vec({0, 1, 2}, {0:24, 1:11, 2:4})
column_row_vector_multiplication3 = Vec({0, 1, 2, 3}, {0:4, 1:8, 2:11, 3:3})
column_row_vector_multiplication4 = Vec({0,1}, {0:30, 1:16})
column_row_vector_multiplication5 = Vec({0, 1, 2}, {0:-3, 1:1, 2:9})

## Problem 11
def lin_comb_mat_vec_mult(M, v):
    assert(M.D[1] == v.D)
    return sum([v[key] * value for (key, value) in mat2coldict(M).items()])

## Problem 12
def lin_comb_vec_mat_mult(v, M):
    assert(v.D == M.D[0])
    return sum([v[key] * value for (key, value) in mat2rowdict(M).items()])

## Problem 13
def dot_product_mat_vec_mult(M, v):
    assert(M.D[1] == v.D)
    return Vec(M.D[0], {key : u * v for (key, u) in mat2rowdict(M).items()})

## Problem 14
def dot_product_vec_mat_mult(v, M):
    assert(v.D == M.D[0])
    return Vec(M.D[1], {key : v * u for (key, u) in mat2coldict(M).items()})

## Problem 15
def Mv_mat_mat_mult(A, B):
    assert A.D[1] == B.D[0]
    C = Mat((A.D[0], B.D[1]), {})
    for (j, v) in mat2coldict(B).items():
        u = A * v
        for i in A.D[0]:
            C[(i, j)] = u[i]
    return C

## Problem 16
def vM_mat_mat_mult(A, B):
    assert A.D[1] == B.D[0]
    C = Mat((A.D[0], B.D[1]), {})
    for (i, u) in mat2rowdict(A).items():
        v = u * B
        for j in B.D[1]:
            C[(i, j)] = v[j]
    return C

## Problem 17
def dot_prod_mat_mat_mult(A, B):
    assert A.D[1] == B.D[0]
    return Mat((A.D[0], B.D[1]), {(i, j) : u * v for (i, u) in mat2rowdict(A).items() for (j, v) in mat2coldict(B).items()})

## Problem 18
solving_systems_x1 = -0.2
solving_systems_x2 = 0.4
solving_systems_y1 = 0.8
solving_systems_y2 = -0.6
solving_systems_m = Mat(({0, 1}, {0, 1}), {(0, 0) : -0.2, (0, 1) : 0.8, (1, 0) : 0.4, (1, 1) : -0.6})
solving_systems_a = Mat(({0, 1}, {0, 1}), {(0, 0) : 3, (0, 1) : 4, (1, 0) : 2, (1, 1) : 1})
solving_systems_a_times_m = Mat(({0, 1}, {0, 1}), {(0, 0) : 1, (0, 1) : 0, (1, 0) : 0, (1, 1) : 1})
solving_systems_m_times_a = Mat(({0, 1}, {0, 1}), {(0, 0) : 1, (0, 1) : 0, (1, 0) : 0, (1, 1) : 1})

## Problem 19
are_inverses1 = True
are_inverses2 = True
are_inverses3 = False
are_inverses4 = False

