rearCam.position.copy(camera.position);
rearTarget.copy(camera.position);
rearTarget.add(camera.position);
rearTarget.sub(cameraControls.target);
rearCam.lookAt(rearTarget);