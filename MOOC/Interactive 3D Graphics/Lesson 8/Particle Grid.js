for ( var x = -1000; x <= 1000; x += 100 ) {
    for ( var y = -1000; y <= 1000; y += 100 ) {
        for ( var z = -1000; z <= 1000; z += 100 ) {
            var vertex = new THREE.Vector3(x, y, z);
            geometry.vertices.push(vertex);
        }
    }
}