frontCam = new THREE.OrthographicCamera( 
    -aspectRatio*viewSize / 2, aspectRatio*viewSize / 2, 
    viewSize / 2, -viewSize / 2, 
    -1000, 1000 );
frontCam.up.set(0,1,0);
    
sideCam = new THREE.OrthographicCamera( 
    -aspectRatio*viewSize / 2, aspectRatio*viewSize / 2, 
    viewSize / 2, -viewSize / 2, 
    -1000, 1000 );
sideCam.up.set(0,1,0);


frontCam.position.copy(cameraControls.target);
frontCam.position.x -= 1;
frontCam.lookAt(cameraControls.target);
renderer.setViewport(0, 0.5*canvasHeight, 0.5*canvasWidth, 0.5*canvasHeight);
renderer.render(scene, frontCam);
    
sideCam.position.copy(cameraControls.target);
sideCam.position.z += 1;
sideCam.lookAt(cameraControls.target);
renderer.setViewport(0.5*canvasWidth, 0, 0.5*canvasWidth, 0.5*canvasHeight);
renderer.render(scene, sideCam);