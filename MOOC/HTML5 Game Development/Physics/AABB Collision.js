intersectRect = function(r1, r2) {
    return Math.max(r1.left, r1.right) >= Math.min(r2.left, r2.right) &&
        Math.max(r1.top, r1.bottom) >= Math.min(r2.top, r2.bottom) &&
        Math.max(r2.left, r2.right) >= Math.min(r1.left, r1.right) &&
        Math.max(r2.top, r2.bottom) >= Math.min(r1.top, r1.bottom);
};