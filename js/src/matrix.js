/**
 * The matrix.
 * The indices start from 1 in the matrix.
 * @author ZHG <CyberZHG@gmail.com>
 */
var Matrix = {
	/**
	 * Create a new matrix object filled with complex 0.
	 * @param {int} rowNum The number of rows of the matrix.
	 * @param {int} colNum The number of columns of the matrix.
	 * @return {matrix} The matrix object.
	 */
	New: function(rowNum, colNum) {
		rowNum = arguments[0] ? arguments[0] : 1;
		colNum = arguments[1] ? arguments[1] : 1;
		var matrix = {
			rowNum: rowNum,
			colNum: colNum,
			data: new Array(rowNum * colNum),
			/**
			 * Calculate the position in the data array with the given row and column.
			 * @param {int} row The index of the row.
			 * @param {int} col The index of the column.
			 * @return {int} The position in the data array.
			 */
			pos: function(row, col) {
				return (row - 1) * this.colNum + col - 1;
			},
			/**
			 * Get data from matrix.
			 * @param {int} row The index of the row.
			 * @param {int} col The index of the column.
			 * @return {complex} The value of the matrix, returns complex 0 if any index is illegal.
			 */
			get: function(row, col) {
				if (row >= 1 && row <= this.rowNum) {
					if (col >= 1 && col <= this.colNum) {
						return this.data[this.pos(row, col)];
					}
				}
				return Complex.New();
			},
			/**
			 * Set data to matrix.
			 * @param {int} row The index of the row.
			 * @param {int} col The index of the column.
			 */
			set: function(row, col, value) {
				if (row >= 1 && row <= this.rowNum) {
					if (col >= 1 && col <= this.colNum) {
						this.data[this.pos(row, col)] = value;
					}
				}
			}
		};
		for (var i = 1; i <= rowNum; ++i) {
			for (var j = 1; j <= colNum; ++j) {
				matrix.set(i, j, Complex.New());
			}
		}
		return matrix;
	}
};