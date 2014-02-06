    update: function () {
        gGameEngine.updatePlayer();
        for (var i = 0; i < gGameEngine.entities.length; ++i) {
            gGameEngine.entities[i].update();
        }
    },