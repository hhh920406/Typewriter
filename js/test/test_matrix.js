test("Matrix", function() {
    var a = Matrix.New(3, 4);
    a.set(1, 2, Complex.New(2.0));
    ok(a.get(1, 2).equal(Complex.New(2.0)), "Set/Get");
    ok(a.get(2, 3).equal(Complex.New(0.0)), "Set/Get");
    var b = Matrix.New(3, 3);
    var c = Matrix.New(3, 3);
    for (var i = 1; i <= 3; ++i) {
        for (var j = 1; j <= 3; ++j) {
            b.set(i, j, ((i - 1) * 3 + j) * 2 - 1);
            c.set(i, j, ((i - 1) * 3 + j) * 2);
        }
    }
    a = Matrix.New(3, 3);
    a.set(1, 1, 3); a.set(1, 2, 7); a.set(1, 3, 11);
    a.set(2, 1, 15); a.set(2, 2, 19); a.set(2, 3, 23);
    a.set(3, 1, 27); a.set(3, 2, 31); a.set(3, 3, 35);
    ok(a.equal(b.add(c)), "Add");
    a.set(1, 1, -1); a.set(1, 2, -1); a.set(1, 3, -1);
    a.set(2, 1, -1); a.set(2, 2, -1); a.set(2, 3, -1);
    a.set(3, 1, -1); a.set(3, 2, -1); a.set(3, 3, -1);
    ok(a.equal(b.sub(c)), "Subtract");
    a.set(1, 1, 96); a.set(1, 2, 114); a.set(1, 3, 132);
    a.set(2, 1, 240); a.set(2, 2, 294); a.set(2, 3, 348);
    a.set(3, 1, 384); a.set(3, 2, 474); a.set(3, 3, 564);
    ok(a.equal(b.mul(c)), "Multiply 1");
    a.set(1, 1, 108); a.set(1, 2, 132); a.set(1, 3, 156);
    a.set(2, 1, 234); a.set(2, 2, 294); a.set(2, 3, 354);
    a.set(3, 1, 360); a.set(3, 2, 456); a.set(3, 3, 552);
    ok(a.equal(c.mul(b)), "Multiply 2");
});
