SimpleProjectileClass = WeaponInstanceClass.extend({
    physBody: null,
    speed: 800,
    init: function (x, y, settings) {
        this.parent(x, y, settings);
        var startPos = settings.pos;
        this.lifetime = 2;
        var entityDef = {
            id: "SimpleProjectile",
            x: startPos.x,
            y: startPos.y,
            halfHeight: 5 * 0.5,
            halfWidth: 5 * 0.5,
            damping: 0
        };
        this.physBody = gPhysicsEngine.addBody(entityDef);
    },
    update: function () {
        this.lifetime -= 0.05;
        if(this.lifetime <= 0) {
            this.kill();
            return;
        }
        this.pos = this.physBody.GetPosition();
        this.parent();
    }
});