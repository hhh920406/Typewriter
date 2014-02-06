InputEngineClass = Class.extend({
    keyState: Array(),
    setup: function () {
        document.getElementById('my_canvas').addEventListener('mousemove', this.onMouseMove);
        document.getElementById('my_canvas').addEventListener('keydown', this.onKeyDown);
        document.getElementById('my_canvas').addEventListener('keyup', this.onKeyUp);
    },
    onMouseMove: function (event) {
        var posx = event.clientX;
        var posy = event.clientY;
    },
    onKeyDown: function (event) {
        this.keyState[event.keyID] = true;
    },
    onKeyUp: function (event) {
        this.keyState[event.keyID] = false;
    },
    update: function() {
        KeyW = 87;
        if(this.keyState[KeyW])
            console.log("FORWARD!!!");
    }
});
gInputEngine = new InputEngineClass();