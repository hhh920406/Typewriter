function PolygonGeometry(sides, location) {
    var geo = new THREE.Geometry();
    for (var pt = 0; pt < sides; ++pt) {
        var angle = (Math.PI / 2) + (pt / sides) * 2 * Math.PI;
        var x = location.x + Math.cos(angle);
        var y = location.y + Math.sin(angle);
        geo.vertices.push(new THREE.Vector3(x, y, 0));
    }
    for (pt = 2; pt < sides; ++pt) {
        geo.faces.push(new THREE.Face3(0, pt - 1, pt));
    }
    return geo;
}

