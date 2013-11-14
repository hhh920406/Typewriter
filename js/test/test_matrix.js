test("Matrix", function() {
	var a = Matrix.New(3, 4);
	a.set(1, 2, Complex.New(2.0));
	ok(a.get(1, 2).equal(Complex.New(2.0)), "Set/Get");
	ok(a.get(2, 3).equal(Complex.New(0.0)), "Set/Get");
});
