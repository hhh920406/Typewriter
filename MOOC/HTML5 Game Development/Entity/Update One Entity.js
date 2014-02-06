LandmineClass = EntityClass.extend({
    lifetime: 100,
    kill: function() {
        gGameEngine.removeEntity(this);
    },

    update: function() {
        this.lifetime -= 0.05;
        if (this.lifetime <= 0) {
            this.kill();
        }
    }
});
gGameEngine.factory['Landmine'] = LandmineClass;