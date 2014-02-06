function setupGui() {
    effectController = {
        fov: 40
    };
    var gui = new dat.GUI();
    var element = gui.add(effectController, "fov", 1.0, 179.0);
    element.name("field of view");
}

function render() {
    var delta = clock.getDelta();
    cameraControls.update(delta);
    camera.fov = effectController.fov;
    camera.updateProjectionMatrix();
    renderer.render(scene, camera);
}