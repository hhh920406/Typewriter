handRight = new THREE.Object3D();
createRobotGrabber(handRight, handLength, robotHandRightMaterial);
handRight.position.y = faLength;
forearm.add(handRight);

handRight.rotation.z = effectController.hz * Math.PI/180;
handRight.position.z = - effectController.htz;