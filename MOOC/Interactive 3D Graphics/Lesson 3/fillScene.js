function fillScene() {
    scene = new THREE.Scene();
    var material, geometry, mesh;
    material = new THREE.MeshBasicMaterial({vertexColors: THREE.VertexColors, side: THREE.DoubleSide});
    geometry = new THREE.Geometry();
    geometry.vertices.push(new THREE.Vector3(100, 0, 0));
    geometry.vertices.push(new THREE.Vector3(0, 100, 0));
    geometry.vertices.push(new THREE.Vector3(0, 0, 100));
    geometry.faces.push(new THREE.Face3(0, 1, 2));
    var color1 = new THREE.Color(0xFF0000);
    var color2 = new THREE.Color(0x00FF00);
    var color3 = new THREE.Color(0x0000FF);
    geometry.faces[0].vertexColors = [color1, color2, color3];
    mesh = new THREE.Mesh(geometry, material);
    scene.add(mesh);
}