function createBall() {
    var material = new THREE.MeshLambertMaterial( { color: 0xFF0000, shading: THREE.FlatShading } );
    var ka = 0.4;
    material.ambient.setRGB( material.color.r * ka, material.color.g * ka, material.color.b * ka );
    material.shading = THREE.FlatShading;
    var sphere = new THREE.Mesh(
        new THREE.SphereGeometry( 400, 64, 32 ), material );
    return sphere;
}