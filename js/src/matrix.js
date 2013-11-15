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
                        if (typeof(value) == "number") {
                            value = Complex.New(value);
                        }
                        this.data[this.pos(row, col)] = value;
                    }
                }
            },
            /**
             * Add with another matrix.
             * @param {matrix} Another matrix.
             * @return {matrix} The added result.
             */
            add: function(mat) {
                var res = Matrix.New(this.rowNum, this.colNum);
                for (var i = 1; i <= this.rowNum; ++i) {
                    for (var j = 1; j <= this.colNum; ++j) {
                        res.set(i, j, this.get(i, j).add(mat.get(i, j)));
                    }
                }
                return res;
            },
            /**
             * Subtract to another matrix.
             * @param {matrix} Another matrix.
             * @return {matrix} The subtracted result.
             */
            sub: function(mat) {
                var res = Matrix.New(this.rowNum, this.colNum);
                for (var i = 1; i <= this.rowNum; ++i) {
                    for (var j = 1; j <= this.colNum; ++j) {
                        res.set(i, j, this.get(i, j).sub(mat.get(i, j)));
                    }
                }
                return res;
            },
            /**
             * Multiply with another matrix.
             * @param {matrix} Another matrix.
             * @return {matrix} The multiplied result.
             */
            mul: function(mat) {
                var res = Matrix.New(this.rowNum, mat.colNum);
                for (var i = 1; i <= this.rowNum; ++i) {
                    for (var j = 1; j <= mat.colNum; ++j) {
                        for (var k = 1; k <= this.colNum; ++k) {
                            res.set(i, j, res.get(i, j).add(this.get(i, k).mul(mat.get(k, j))));
                        }
                    }
                }
                return res;
            },
            /**
             * Whether the matrix equals to another.
             * @param {matrix} mat Another matrix.
             * @return {boolean} Returns true if equals, otherwise false.
             */
            equal: function(mat) {
                for (var i = 1; i <= this.rowNum; ++i) {
                    for (var j = 1; j <= this.colNum; ++j) {
                        if (!this.get(i, j).equal(mat.get(i, j))) {
                            return false;
                        }
                    }
                }
                return true;
            },
            /**
             * Returns a string represents the complex.
             * @return {string} The string
             */
            str: function() {
                var res = "[";
                for (var i = 1; i <= this.rowNum; ++i) {
                    for (var j = 1; j <= this.colNum; ++j) {
                        res += " " + this.get(i, j).str();
                    }
                    if (i != this.rowNum) {
                        res += ";";
                    }
                }
                res += "]";
                return res;
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