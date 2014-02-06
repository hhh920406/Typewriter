    spawnEntity: function (typename) {
        return new gGameEngine.factory[typename]();
    }