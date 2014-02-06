cube = new THREE.Mesh(
    new THREE.CubeGeometry( 70, 4, 4 ), minuteHandMaterial );
cube.position.y = 14;
cube.position.x = 70/2 - 10;

var cube3D = new THREE.Object3D();
cube3D.add(cube);
cube3D.rotation.y = -60 * Math.PI/180;
scene.add(cube3D);

var sphere = new THREE.Mesh(
    new THREE.SphereGeometry( 0.5, 32, 16 ), hourHandMaterial );
sphere.position.y = 18;
sphere.position.x = 50/2 - 10;
sphere.scale.x = 50;
sphere.scale.y = 4;
sphere.scale.z = 4;

var sphere3D = new THREE.Object3D();
sphere3D.add(sphere);
sphere3D.rotation.y = 30 * Math.PI/180;
scene.add(sphere3D);