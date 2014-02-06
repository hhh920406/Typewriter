/**
 * The complex number.
 * @author ZHG <CyberZHG@gmail.com>
 */
var Complex = {
    /**
     * Create a new complex number object.
     * @param {double} real The real part of the complex number.
     * @param {double} image The image part of the complex number.
     * @return {complex} The complex number object.
     */
    New: function(real, image) {
        real = arguments[0] ? arguments[0] : 0.0;
        image = arguments[1] ? arguments[1] : 0.0;
        var complex = {
            real: real,
            image: image,
            /**
             * Add with another complex number.
             * @param {complex} num A complex number.
             * @return {complex} The added result.
             */
            add: function(num) {
                var res = Complex.New();
                if (typeof(num) == "number") {
                    res.real = this.real + num;
                } else {
                    res.real = this.real + num.real;
                    res.image = this.image + num.image;
                }
                return res;
            },
            /**
             * Subtract to another complex number.
             * @param {complex} num A complex number.
             * @return {complex} The subtracted result.
             */
            sub: function(num) {
                var res = Complex.New();
                if (typeof(num) == "number") {
                    res.real = this.real - num;
                } else {
                    res.real = this.real - num.real;
                    res.image = this.image - num.image;
                }
                return res;
            },
            /**
             * Multiply with another complex number.
             * @param {complex} num A complex number.
             * @return {complex} The multiplied result.
             */
            mul: function(num) {
                var res = Complex.New();
                if (typeof(num) == "number") {
                    res.real = this.real * num;
                    res.image = this.image * num;
                } else {
                    res.real = this.real * num.real - this.image * num.image;
                    res.image = this.real * num.image + this.image * num.real;
                }
                return res;
            },
            /**
             * Divide to another complex number.
             * @param {complex} num A complex number.
             * @return {complex} The divided result.
             */
            div: function(num) {
                var res = Complex.New();
                if (typeof(num) == "number") {
                    res.real = this.real / num;
                    res.image = this.image / num;
                } else {
                    res = this.mul(num.conj());
                    var scale = num.real * num.real + num.image * num.image;
                    res.real /= scale;
                    res.image /= scale;
                }
                return res;
            },
            /**
             * Whether the complex number equals to another.
             * @param {complex} num A complex number.
             * @return {boolean} Returns true if equals, otherwise false.
             */
            equal: function(num) {
                if (typeof(num) == "number") {
                    return Math.abs(this.real - num) < 1e-8 && Math.abs(this.image) < 1e-8
                }
                return Math.abs(this.real - num.real) < 1e-8 && Math.abs(this.image - num.image) < 1e-8;
            },
            /**
             * Calculate the norm of the complex number.
             * @return {double} norm.
             */
            norm: function() {
                return Math.sqrt(this.real * this.real + this.image * this.image);
            },
            /**
             * Calculate the phase angle of the complex number.
             * @return {double} Phase angle.
             */
            angle: function() {
                return Math.atan2(this.image, this.real);
            },
            /**
             * Calculate the conjugate of the complex number.
             * @return {complex} The conjugated complex number.
             */
            conj: function() {
                var res = Complex.New();
                res.real = this.real;
                res.image = - this.image;
                return res;
            },
            /**
             * Returns a string represents the complex.
             * @return {string} The string
             */
            str: function() {
                var res = "" + this.real;
                if (Math.abs(this.image) > 1e-8) {
                    if (this.image > 0) {
                        res += " + ";
                    } else {
                        res += " - ";
                    }
                    res += Math.abs(this.image) + "i";
                }
                return res;
            }
        }
        return complex;
    },
    /**
     * Create the complex 1.
     * @return {complex} The complex.
     */
    one: function() {
        return this.New(1.0);
    },
    zero: function() {
        return this.New();
    },
};