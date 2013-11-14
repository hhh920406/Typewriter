var Complex = {
	New: function(realPart, imagePart) {
		realPart = arguments[0] ? arguments[0] : 0.0;
		imagePart = arguments[1] ? arguments[1] : 0.0;
		var complex = {
			real: realPart,
			image: imagePart,
			add: function(num) {
				var res = Complex.New();
				res.real = this.real + num.real;
				res.image = this.image + num.image;
				return res;
			},
			sub: function(num) {
				var res = Complex.New();
				res.real = this.real - num.real;
				res.image = this.image - num.image;
				return res;
			},
			mul: function(num) {
				var res = Complex.New();
				res.real = this.real * num.real - this.image * num.image;
				res.image = this.real * num.image + this.image * num.real;
				return res;
			},
			div: function(num) {
				var res = this.mul(num.conjugate());
				var scale = num.real * num.real + num.image * num.image;
				res.real /= scale;
				res.image /= scale;
				return res;
			},
			equal: function(num) {
				return Math.abs(this.real - num.real) < 1e-8 && Math.abs(this.image - num.image) < 1e-8
			},
			norm: function() {
				return Math.sqrt(this.real * this.real + this.image * this.image);
			},
			angle: function() {
				return Math.atan2(this.image, this.real);
			},
			conjugate: function() {
				var res = Complex.New();
				res.real = this.real;
				res.image = - this.image;
				return res;
			}
		}
		return complex;
	}
};