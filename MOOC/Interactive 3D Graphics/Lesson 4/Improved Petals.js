for (var i = 0; i < 24; ++i) {
    var cylinder = new THREE.Mesh(cylGeom, petalMaterial);
    cylinder.scale.x = 0.25;
    cylinder.position.y = petalLength / 2;
    var petal = new THREE.Object3D();
    petal.add(cylinder);
    petal.position.y = flowerHeight;
    petal.rotation.y = 360 / 24 * i * Math.PI/180;
    petal.rotation.z = (90 - 20) * Math.PI/180;
    flower.add(petal);
}