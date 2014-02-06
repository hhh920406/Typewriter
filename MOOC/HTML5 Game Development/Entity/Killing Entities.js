    update: function () {
        gGameEngine.updatePlayer();
        for (var i = 0; i < gGameEngine.entities.length; i++) {
            var ent = gGameEngine.entities[i];
            if (!ent._killed) {
                ent.update();
            }
        }
    }