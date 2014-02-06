package com.zsys.main;

public class Matrix {
	private int row;
	private int column;
	public double m[][];
	
	public Matrix() {
		this.row = 3;
		this.column = 3;
		this.m = new double[this.row][this.column];
	}
	
	public int getRow() {
		return row;
	}
	public void setRow(int row) {
		if(this.row != row && row >= 1) {
			this.row = row;
			this.m = new double[this.row][this.column];
		}
	}
	
	public int getColumn() {
		return column;
	}
	
	public void setColumn(int column) {
		if(this.column != column) {
			this.column = column;
			this.m = new double[this.row][this.column];
		}
	}
	
	public void setSize(int row, int column) {
		if(row >= 1 && column >= 1) {
			if(this.row != row || this.column != column) {
				this.row = row;
				this.column = column;
				this.m = new double[this.row][this.column];
			}
		}
	}
	
	public static Matrix unitMatrix(int size) {
		Matrix matrix = new Matrix();
		matrix.setSize(size, size);
		for(int i=0;i<size;++i) {
			matrix.m[i][i] = 1.0;
			for(int j=i+1;j<size;++j) {
				matrix.m[i][j] = matrix.m[j][i] = 0.0;
			}
		}
		return matrix;
	}
	
	public static Matrix unitMatrix(int row, int column) {
		Matrix matrix = new Matrix();
		matrix.setSize(row, column);
		for(int i=0;i<row;++i) {
			for(int j=0;j<column;++j) {
				if(i == j) {
					matrix.m[i][j] = 1.0;
				} else {
					matrix.m[i][j] = 0.0;
				}
			}
		}
		return matrix;
	}
	
	public static Matrix zeroMatrix(int row, int column) {
		Matrix matrix = new Matrix();
		matrix.setSize(row, column);
		for(int i=0;i<row;++i) {
			for(int j=0;j<column;++j) {
				matrix.m[i][j] = 0.0;
			}
		}
		return matrix;
	}
	
	public static Matrix oneMatrix(int row, int column) {
		Matrix matrix = new Matrix();
		matrix.setSize(row, column);
		for(int i=0;i<row;++i) {
			for(int j=0;j<column;++j) {
				matrix.m[i][j] = 1.0;
			}
		}
		return matrix;
	}
	
	public void clone(Matrix m) {
		this.setSize(m.getRow(), m.getColumn());
		for(int i=0;i<this.row;++i) {
			for(int j=0;j<this.column;++j) {
				this.m[i][j] = m.m[i][j];
			}
		}
	}
	
	public Matrix add(Matrix m) {
		Matrix matrix = new Matrix();
		matrix.setSize(this.row, this.column);
		for(int i=0;i<matrix.row;++i) {
			for(int j=0;j<matrix.column;++j) {
				matrix.m[i][j] = this.m[i][j] + m.m[i][j];
			}
		}
		return matrix;
	}
	
	public Matrix substract(Matrix m) {
		Matrix matrix = new Matrix();
		matrix.setSize(this.row, this.column);
		for(int i=0;i<matrix.row;++i) {
			for(int j=0;j<matrix.column;++j) {
				matrix.m[i][j] = this.m[i][j] - m.m[i][j];
			}
		}
		return matrix;
	}
	
	public Matrix multiply(Matrix m) {
		Matrix matrix = new Matrix();
		matrix.setSize(this.row, m.column);
		for(int i=0;i<matrix.row;++i) {
			for(int j=0;j<matrix.column;++j) {
				matrix.m[i][j] = 0.0;
				for(int k=0;k<this.column;++k) {
					matrix.m[i][j] += this.m[i][k] * m.m[k][j];
				}
			}
		}
		return matrix;
	}
	
	public Matrix multiply(double coe) {
		Matrix matrix = new Matrix();
		matrix.setSize(this.row, this.column);
		for(int i=0;i<matrix.row;++i) {
			for(int j=0;j<matrix.column;++j) {
				matrix.m[i][j] = this.m[i][j] * coe;
			}
		}
		return matrix;
	}
	
	public Matrix copy() {
		Matrix matrix = new Matrix();
		matrix.setSize(this.row, this.column);
		for(int i=0;i<this.row;++i) {
			for(int j=0;j<this.column;++j) {
				matrix.m[i][j] = this.m[i][j];
			}
		}
		return matrix;
	}
	
	public Matrix rowExchange(int r1, int r2) {
		Matrix matrix = this.copy();
		double temp;
		for(int i=0;i<this.column;++i) {
			temp = matrix.m[r1][i];
			matrix.m[r1][i] = matrix.m[r2][i];
			matrix.m[r2][i] = temp;
		}
		return matrix;
	}
	
	public Matrix columnExchange(int c1, int c2) {
		Matrix matrix = this.copy();
		double temp;
		for(int i=0;i<this.row;++i) {
			temp = matrix.m[i][c1];
			matrix.m[i][c1] = matrix.m[i][c2];
			matrix.m[i][c2] = temp;
		}
		return matrix;
	}
	
	public Matrix transpose() {
		Matrix matrix = new Matrix();
		matrix.setSize(this.column, this.row);
		for(int i=0;i<this.column;++i) {
			for(int j=0;j<this.row;++j) {
				matrix.m[i][j] = this.m[j][i];
			}
		}
		return matrix;
	}
	
	public Matrix upperTriangular() {
		Matrix matrix = new Matrix();
		matrix.setSize(this.row, this.column);
		for(int i=0;i<this.row;++i) {
			for(int j=0;j<this.column;++j) {
				if(j >= i) {
					matrix.m[i][j] = this.m[i][j];
				} else {
					matrix.m[i][j] = 0.0;
				}
			}
		}
		return matrix;
	}
	
	public Matrix lowerTriangular() {
		Matrix matrix = new Matrix();
		matrix.setSize(this.row, this.column);
		for(int i=0;i<this.row;++i) {
			for(int j=0;j<this.column;++j) {
				if(j <= i) {
					matrix.m[i][j] = this.m[i][j];
				} else {
					matrix.m[i][j] = 0.0;
				}
			}
		}
		return matrix;
	}
	
	public boolean isSquareMatrix() {
		return this.row == this.column;
	}
	
	public boolean isRowAgree(Matrix m) {
		return this.row == m.row;
	}
	
	public boolean isColumnAgree(Matrix m) {
		return this.column == m.column;
	}
	
	public boolean isDimentionAgree(Matrix m) {
		return this.row == m.getRow() && this.column == m.column;
	}
	
	public boolean isInnerDimentionAgree(Matrix m) {
		return this.column == m.row;
	}
	
	public Matrix determinant() {
		Matrix matrix = new Matrix();
		matrix.setSize(1, 1);
		matrix.m[0][0] = determinant(this);
		return matrix;
	}
	
	public double determinant(Matrix m) {
		if(m.row == 1 || m.column == 1) {
			return m.m[0][0];
		}
		double result = 0.0;
		boolean positive = true;
		for(int i=0;i<m.column;++i) {
			if(positive) {
				result += m.m[0][i] * determinant(m.cofactor(0, i));
			} else {
				result -= m.m[0][i] * determinant(m.cofactor(0, i));
			}
			positive = ! positive;
		}
		return result;
	}
	
	public Matrix cofactor(int r, int c) {
		Matrix matrix = new Matrix();
		matrix.setSize(this.row - 1, this.column - 1);
		int i2 = 0;
		for(int i1=0;i1<this.row;++i1) {
			if(i1 == r) {
				continue;
			}
			int j2 = 0;
			for(int j1=0;j1<this.column;++j1) {
				if(j1 == c) {
					continue;
				}
				matrix.m[i2][j2] = this.m[i1][j1];
				++ j2;
			}
			++ i2;
		}
		return matrix;
	}
	
	public Matrix horizonMerger(Matrix m) {
		Matrix matrix = new Matrix();
		matrix.setSize(this.row, this.column + m.column);
		for(int i=0;i<this.row;++i) {
			for(int j=0;j<this.column;++j) {
				matrix.m[i][j] = this.m[i][j];
			}
		}
		for(int i=0;i<m.row;++i) {
			for(int j=0;j<m.column;++j) {
				matrix.m[i][j + this.column] = m.m[i][j];
			}
		}
		return matrix;
	}
	
	public Matrix verticalMerger(Matrix m) {
		Matrix matrix = new Matrix();
		matrix.setSize(this.row + m.row, this.column);
		for(int i=0;i<this.row;++i) {
			for(int j=0;j<this.column;++j) {
				matrix.m[i][j] = this.m[i][j];
			}
		}
		for(int i=0;i<m.row;++i) {
			for(int j=0;j<m.column;++j) {
				matrix.m[i + this.row][j] = m.m[i][j];
			}
		}
		return matrix;
	}
	
	public Matrix subMatrix(int r1, int c1, int r2, int c2) {
		Matrix matrix = new Matrix();
		matrix.setSize(r2 - r1 + 1, c2 - c1 + 1);
		for(int i=r1;i<=r2;++i) {
			for(int j=c1;j<=c2;++j) {
				matrix.m[i - r1][j - c1] = this.m[i][j];
			}
		}
		return matrix;
	}
	
	public Matrix adjont() {
		Matrix matrix = new Matrix();
		matrix.setSize(this.row, this.column);
		for(int i=0;i<this.row;++i) {
			for(int j=0;j<this.column;++j) {
				if( ((i+j)&1) == 0) {
					matrix.m[i][j] = this.determinant(this.cofactor(i, j));
				} else {
					matrix.m[i][j] = - this.determinant(this.cofactor(i, j));
				}
			}
		}
		return matrix;
	}
	
	public boolean isInside(int r, int c) {
		return r >= 0 && r < this.row && c >= 0 && c < this.column;
	}
}
