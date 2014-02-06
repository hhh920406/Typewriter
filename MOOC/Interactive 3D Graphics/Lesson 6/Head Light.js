headlight = new THREE.PointLight(0xFFFFFF, 1.0);
scene.add(headlight);

headlight.position.copy(camera.position);