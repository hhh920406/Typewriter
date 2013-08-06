function render() {
    var delta = clock.getDelta();
    cameraControls.update(delta);
    light.position.x = Math.cos(effectController.angle * Math.PI / 180);
    light.position.z = Math.sin(effectController.angle * Math.PI / 180);
    renderer.render(scene, camera);
}