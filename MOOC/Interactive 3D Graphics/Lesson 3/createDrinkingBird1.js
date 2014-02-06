function createDrinkingBird() {
    var headMaterial = new THREE.MeshPhongMaterial();
    headMaterial.color.r = 104/255;
    headMaterial.color.g = 1/255;
    headMaterial.color.b = 5/255;
    headMaterial.specular.setRGB(0.5, 0.5, 0.5);

    var hatMaterial = new THREE.MeshPhongMaterial({shininess: 100});
    hatMaterial.color.r = 24/255;
    hatMaterial.color.g = 38/255;
    hatMaterial.color.b = 77/255;
    hatMaterial.specular.setRGB(0.5, 0.5, 0.5);

    var bodyMaterial = new THREE.MeshPhongMaterial({shininess: 100});
    bodyMaterial.color.setRGB( 31/255, 86/255, 169/255 );
    bodyMaterial.specular.setRGB(0.5, 0.5, 0.5);

    var legMaterial = new THREE.MeshPhongMaterial({shininess: 4});
    legMaterial.color.setHex( 0xAdA79b );
    legMaterial.specular.setRGB(0.5, 0.5, 0.5);

    var footMaterial = new THREE.MeshPhongMaterial({color: 0x960f0b, shininess: 30});
    footMaterial.specular.setRGB(0.5, 0.5, 0.5);

    var sphere, cylinder, cube;

    var bevelRadius = 1.9;

    cube = new THREE.Mesh(new THREE.BeveledBlockGeometry( 20+64+110, 4, 2*77+12, bevelRadius ), footMaterial );
    cube.position.x = -45; 
    cube.position.y = 4/2;
    cube.position.z = 0;
    scene.add( cube );

    cube = new THREE.Mesh(
        new THREE.BeveledBlockGeometry( 20+64+110, 52, 6, bevelRadius ), footMaterial );
    cube.position.x = -45;
    cube.position.y = 52/2;
    cube.position.z = 77 + 6/2;
    scene.add( cube );

    cube = new THREE.Mesh(
        new THREE.BeveledBlockGeometry( 20+64+110, 52, 6, bevelRadius ), footMaterial );
    cube.position.x = -45;
    cube.position.y = 52/2;
    cube.position.z = -(77 + 6/2);
    scene.add( cube );

    cube = new THREE.Mesh(
        new THREE.BeveledBlockGeometry( 64, 104, 6, bevelRadius ), footMaterial );
    cube.position.x = 0;
    cube.position.y = 104/2;
    cube.position.z = 77 + 6/2;
    scene.add( cube );

    cube = new THREE.Mesh(
        new THREE.BeveledBlockGeometry( 64, 104, 6, bevelRadius ), footMaterial );
    cube.position.x = 0;
    cube.position.y = 104/2;
    cube.position.z = -(77 + 6/2);
    scene.add( cube );

    cube = new THREE.Mesh(
        new THREE.BeveledBlockGeometry( 60, 282+4, 4, bevelRadius ), legMaterial );
    cube.position.x = 0;
    cube.position.y = 104 + 282/2 - 2;
    cube.position.z = 77 + 6/2;
    scene.add( cube );

    cube = new THREE.Mesh(
        new THREE.BeveledBlockGeometry( 60, 282+4, 4, bevelRadius ), legMaterial );
    cube.position.x = 0;
    cube.position.y = 104 + 282/2 - 2;
    cube.position.z = -(77 + 6/2);
    scene.add( cube );

    sphere = new THREE.Mesh(
        new THREE.SphereGeometry( 116/2, 32, 16 ), bodyMaterial );
    sphere.position.x = 0;
    sphere.position.y = 160;
    sphere.position.z = 0;
    scene.add( sphere );

    cylinder = new THREE.Mesh(
        new THREE.CylinderGeometry( 24/2, 24/2, 390, 32 ), bodyMaterial );
    cylinder.position.x = 0;
    cylinder.position.y = 160 + 390/2;
    cylinder.position.z = 0;
    scene.add( cylinder );

    sphere = new THREE.Mesh(
        new THREE.SphereGeometry( 104/2, 32, 16 ), headMaterial );
    sphere.position.x = 0;
    sphere.position.y = 160 + 390;
    sphere.position.z = 0;
    scene.add( sphere );

    cylinder = new THREE.Mesh(
        new THREE.CylinderGeometry( 142/2, 142/2, 10, 32 ), hatMaterial );
    cylinder.position.x = 0;
    cylinder.position.y = 160 + 390 + 40 + 10/2;
    cylinder.position.z = 0;
    scene.add( cylinder );

    cylinder = new THREE.Mesh(
        new THREE.CylinderGeometry( 80/2, 80/2, 70, 32 ), hatMaterial );
    cylinder.position.x = 0;
    cylinder.position.y = 160 + 390 + 40 + 10 + 70/2;
    cylinder.position.z = 0;
    scene.add( cylinder );
}