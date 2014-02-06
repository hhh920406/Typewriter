function drawSquare(x1, y1, x2, y2) {
    var square = new THREE.Geometry();
    square.vertices.push( new THREE.Vector3(x1, y1, 0) );
    square.vertices.push( new THREE.Vector3(x2, y1, 0) );
    square.vertices.push( new THREE.Vector3(x2, y2, 0) );
    square.vertices.push( new THREE.Vector3(x1, y2, 0) );
    square.faces.push( new THREE.Face4(0, 1, 2, 3) );
    return square;
}

