SimpleProjectileClass = WeaponInstanceClass.extend({
    physBody: null,
    lifetime: 0,
    init: function (x, y, settings) {
        this.parent(x, y, settings);
        var startPos = settings.pos;
        this.lifetime = 2;
        var entityDef = {
            id : '',
            x : startPos.x,
            y : startPos.y,
            halfWidth: 0,
            halfHeight: 0,
            damping: 0
        };
        this.physBody = gPhysicsEngine.addBody(entityDef);
    }
});
gGameEngine.factory['SimpleProjectile'] = SimpleProjectileClass;