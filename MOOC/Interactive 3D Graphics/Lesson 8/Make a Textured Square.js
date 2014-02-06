function SquareGeometry() {
    var geo = new THREE.Geometry();
    geo.vertices.push( new THREE.Vector3( 0.0, 0.0, 0.0 ) );
    geo.vertices.push( new THREE.Vector3( 1.0, 0.0, 0.0 ) );
    geo.vertices.push( new THREE.Vector3( 1.0, 1.0, 0.0 ) );
    geo.vertices.push( new THREE.Vector3( 0.0, 1.0, 0.0 ) );
    var uvs = [];
    uvs.push( new THREE.Vector2( 0.0, 0.0 ) );
    uvs.push( new THREE.Vector2( 1.0, 0.0 ) );
    uvs.push( new THREE.Vector2( 1.0, 1.0 ) );
    uvs.push( new THREE.Vector2( 0.0, 1.0 ) );
    
    geo.faces.push( new THREE.Face3( 0, 1, 2 ) );
    geo.faceVertexUvs[ 0 ].push( [ uvs[0], uvs[1], uvs[2] ] );
    geo.faces.push( new THREE.Face3( 0, 2, 3 ) );
    geo.faceVertexUvs[ 0 ].push( [ uvs[0], uvs[2], uvs[3] ] );
    return geo;
}