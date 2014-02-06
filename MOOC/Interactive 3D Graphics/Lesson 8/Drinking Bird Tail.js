var tailTexture = THREE.ImageUtils.loadTexture('/media/img/cs291/textures/feather.png');
    
var tail = new THREE.Mesh(
    new THREE.PlaneGeometry( 100, 100, 1, 1 ),
    new THREE.MeshLambertMaterial( { side: THREE.DoubleSide, map: tailTexture, transparent: true} ) );