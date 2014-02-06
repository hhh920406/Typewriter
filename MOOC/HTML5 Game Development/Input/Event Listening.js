function setup() {
    document.getElementById("my_canvas").addEventListener("mousemove", onMouseMove);
    document.getElementById("my_canvas").addEventListener("keydown", onKeyDown);
}

function onMouseMove(event) {
    var x = event.clientX;
    var y = event.clientY;
    return x;
}

function onKeyDown(event) {
    return event.keyID;
}