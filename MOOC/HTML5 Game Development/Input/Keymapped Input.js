InputEngineClass = Class.extend({
    bindings: {},
    actions: {},
    mouse: {
        x: 0,
        y: 0
    },
    setup: function () {
        gInputEngine.bind(87, 'move-up');
        gInputEngine.bind(65, 'move-left');
        gInputEngine.bind(83, 'move-down');
        gInputEngine.bind(68, 'move-right');
        document.getElementById('my_canvas').addEventListener('mousemove', gInputEngine.onMouseMove);
        document.getElementById('my_canvas').addEventListener('keydown', gInputEngine.onKeyDown);
        document.getElementById('my_canvas').addEventListener('keyup', gInputEngine.onKeyUp);
    },
    onMouseMove: function (event) {
        gInputEngine.mouse.x = event.clientX;
        gInputEngine.mouse.y = event.clientY;
    },
    onKeyDown: function (event) {
        gInputEngine.actions[gInputEngine.bindings[event.keyID]] = true;
    },
    onKeyUp: function (event) {
        gInputEngine.actions[gInputEngine.bindings[event.keyID]] = false;
    },
    bind: function (key, action) {
        gInputEngine.bindings[key] = action;
    }
});
gInputEngine = new InputEngineClass();