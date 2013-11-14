test("Complex", function() {
	var a = Complex.New(3.0, 4.0);
	var b = Complex.New(4.0, 5.0);
	ok(a.real == 3, "Real");
	ok(a.image == 4, "Image");
	ok(a.norm() == 5, "Norm");
	var c = a.conjugate();
	ok(c.real == 3, "Conjugate real");
	ok(c.image == -4, "Conjugate image");
	ok(!a.equal(b), "Unequal");
	ok(a.equal(c.conjugate()), "Equal");
	ok(a.angle() - Math.atan(4.0, 3.0) < 1e-8, "Angle");
	ok(a.add(b).equal(Complex.New(7.0, 9.0)), "Add");
	ok(a.sub(b).equal(Complex.New(-1.0, -1.0)), "Subtract");
	ok(a.mul(b).equal(Complex.New(-8.0, 31.0)), "Multiply");
	ok(a.div(b).equal(Complex.New(0.7804878048780489, 0.02439024390243905)), "Divide");
});