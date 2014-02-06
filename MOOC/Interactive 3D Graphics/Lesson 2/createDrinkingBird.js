// Supporting frame for the bird - base + legs + feet
function createSupport() {
    var cubeMaterial = new THREE.MeshLambertMaterial({ color: 0xF07020 });
    // base
    var cube;
    cube = new THREE.Mesh( 
        new THREE.CubeGeometry(20+64+110, 4, 2*77), cubeMaterial);
    cube.position.x = -45;
    cube.position.y = 4/2;
    cube.position.z = 0;
    scene.add(cube);
	// left foot
    cube = new THREE.Mesh( 
        new THREE.CubeGeometry(20+64+110, 52, 6), cubeMaterial );
    cube.position.x = -45;
    cube.position.y = 52/2;
    cube.position.z = 77 + 6/2;	
    scene.add(cube);
	// left leg
    cube = new THREE.Mesh( 
        new THREE.CubeGeometry(64, 334+52, 6), cubeMaterial );
    cube.position.x = 0;
    cube.position.y = (334+52)/2;
    cube.position.z = 77 + 6/2;
    scene.add( cube );
    // right foot
    cube = new THREE.Mesh(
        new THREE.CubeGeometry(20+64+110, 52, 6), cubeMaterial );
    cube.position.x = -45;
    cube.position.y = 52/2;
    cube.position.z = - 77 - 6/2;
    scene.add(cube);
    // right leg
    cube = new THREE.Mesh(
        new THREE.CubeGeometry(64, 334+52, 6), cubeMaterial );
    cube.position.x = 0;
    cube.position.y = (334+52)/2;
    cube.position.z = - 77 - 6/2;
    scene.add(cube);
}

// Body of the bird - body and the connector of body and head
function createBody() {
    var sphereMaterial = new THREE.MeshLambertMaterial( { color: 0xA00000 } );
    var cylinderMaterial = new THREE.MeshLambertMaterial( { color: 0x0000D0 } );
    var body = new THREE.Mesh(
        new THREE.SphereGeometry(58, 32, 32), sphereMaterial);
    body.position.x = 0;
    body.position.y = 160;
    body.position.z = 0;
    scene.add(body);
    var spine = new THREE.Mesh(
        new THREE.CylinderGeometry(12, 12, 390, 32), cylinderMaterial);
    spine.position.x = 0;
    spine.position.y = 355;
    spine.position.z = 0;
    scene.add(spine);
}

// Head of the bird - head + hat
function createHead() {
    var sphereMaterial = new THREE.MeshLambertMaterial( { color: 0xA00000 } );
    var cylinderMaterial = new THREE.MeshLambertMaterial( { color: 0x0000D0 } );
    var head = new THREE.Mesh(
        new THREE.SphereGeometry(52, 32, 32), sphereMaterial);
    head.position.x = 0;
    head.position.y = 550;
    head.position.z = 0;
    scene.add(head);
    var hat;
    hat = new THREE.Mesh(
        new THREE.CylinderGeometry(71, 71, 10, 32), cylinderMaterial);
    hat.position.x = 0;
    hat.position.y = 595;
    hat.position.z = 0;
    scene.add(hat);
    hat = new THREE.Mesh(
        new THREE.CylinderGeometry(40, 40, 70, 32), cylinderMaterial);
    hat.position.x = 0;
    hat.position.y = 635;
    hat.position.z = 0;
    scene.add(hat);
}

function createDrinkingBird() {
	createSupport();
    createBody();
    createHead();
}

