function render() {
    var delta = clock.getDelta();
    cameraControls.update(delta);
    light.position.x = Math.cos(effectController.altitude * Math.PI / 180) * Math.cos(effectController.azimuth * Math.PI / 180);
    light.position.z = Math.cos(effectController.altitude * Math.PI / 180) * Math.sin(effectController.azimuth * Math.PI / 180);
    light.position.y = Math.sin(effectController.altitude * Math.PI / 180);
    renderer.render(scene, camera);
}