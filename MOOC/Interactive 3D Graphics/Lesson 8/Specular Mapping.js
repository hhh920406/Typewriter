function createMaterial() {
    var texture = THREE.ImageUtils.loadTexture('/media/img/cs291/textures/water.jpg');
    var material = new THREE.MeshPhongMaterial( { shininess: 50 } );
    material.color.setHSL( 0.09, 0.46, 0.2 );
    material.ambient.copy( material.color );
    material.specular.setHSL( 0.09, 0.46, 1.0 );
    material.specularMap = texture;
    return material;
}