    update: function () {
        gGameEngine.updatePlayer();
        for (var i = 0; i < gGameEngine.entities.length; i++) {
            var ent = gGameEngine.entities[i];
            if (ent._killed) {
                gGameEngine._deferredKill.push(ent);
            } else {
                ent.update();
            }
        }
        for (var i = 0; i < gGameEngine._deferredKill.length; ++i) {
            for (var j = 0; j < gGameEngine.entities.length; ++j) {
                if (gGameEngine._deferredKill[i] === gGameEngine.entities[j]) {
                    gGameEngine.entities.splice(j, 1);
                    break;
                }
            }
        }
        gGameEngine._deferredKill = [];
    }