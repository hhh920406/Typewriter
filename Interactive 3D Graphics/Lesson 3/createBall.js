function createBall() {
    var material = new THREE.MeshLambertMaterial({color: 0x80FC66, shading: THREE.FlatShading});
    var newR = material.color.r * 0.4;
    var newG = material.color.g * 0.4;
    var newB = material.color.b * 0.4;
    material.ambient.setRGB(newR, newG, newB);
    var sphere = new THREE.Mesh(new THREE.SphereGeometry( 400, 64, 32 ), material);
    return sphere;
}