var light = new THREE.SpotLight(0xFFFFFF, 1.5);
light.position.set(-400, 1200, 300);
light.angle = 20 * Math.PI / 180;
light.exponent = 1;
light.target.position.set(0, 200, 0);
scene.add(light);