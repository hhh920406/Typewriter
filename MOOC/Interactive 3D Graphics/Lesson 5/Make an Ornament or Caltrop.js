for (var x = -1; x <= 1; x += 2) {
    for (var z = -1; z <= 1; z += 2) {
        var cylinder = new THREE.Mesh(new THREE.CylinderGeometry(0.2, 0.2, cylLength, 32), cylinderMaterial);
        var rotationAxis = new THREE.Vector3(x, 0, z);
        rotationAxis.normalize();
        cylinder.matrix.makeRotationAxis(rotationAxis, theta);
        cylinder.matrixAutoUpdate = false;
        scene.add(cylinder);
    }
}