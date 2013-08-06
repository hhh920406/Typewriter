var texture = THREE.ImageUtils.loadTexture( '/media/img/cs291/textures/grass512x512.jpg' );
texture.wrapS = texture.wrapT = THREE.RepeatWrapping;
texture.repeat.set(10, 10);
texture.offset.set(0, 0);

var solidGround = new THREE.Mesh(
    new THREE.PlaneGeometry( 10000, 10000, 100, 100 ),
    new THREE.MeshLambertMaterial( { map: texture } ) );
solidGround.rotation.x = - Math.PI / 2;
    
scene.add( solidGround );