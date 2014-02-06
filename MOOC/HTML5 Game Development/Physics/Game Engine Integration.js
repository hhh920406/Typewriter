GameEngineClass = Class.extend({
    
    entities: [],
    factory: {},
    _deferredKill: [],

    setup: function () {
        gPhysicsEngine.crate();
    },
    
    spawnEntity: function (typename) {
        var ent = new (gGameEngine.factory[typename])();
        gGameEngine.entities.push(ent);
        return ent;
    },

    update: function () {
        for (var i = 0; i < gGameEngine.entities.length; i++) {
            var ent = gGameEngine.entities[i];
            if(!ent._killed) {
                ent.update();
            } else {
                gGameEngine._deferredKill.push(ent);
            }
        }
        for (var j = 0; j < gGameEngine._deferredKill.length; j++) {
            gGameEngine.entities.erase(gGameEngine._deferredKill[j]);
        }
        gGameEngine._deferredKill = [];
        gPhysicsEngine.update();
    }
});

gGameEngine = new GameEngineClass();