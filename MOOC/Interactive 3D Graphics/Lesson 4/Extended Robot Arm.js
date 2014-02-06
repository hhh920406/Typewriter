body = new THREE.Object3D();
var bodyLength = 60;
createRobotBody(body, bodyLength, robotBodyMaterial);
arm.position.y = bodyLength;
body.add(arm);
scene.add(body);