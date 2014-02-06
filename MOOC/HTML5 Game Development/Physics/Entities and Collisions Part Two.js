    init: function (x, y, settings) {
        this.parent(x, y, settings);
        var startPos = settings.pos;

        this.dir = {
            x: settings.dir.x,
            y: settings.dir.y
        };
        this.lifetime = 2;
        var entityDef = {
            id: "SimpleProjectile",
            x: startPos.x,
            y: startPos.y,
            halfHeight: 5 * 0.5,
            halfWidth: 5 * 0.5,
            damping: 0,
            userData: {
                id : '',
                ent : this
            }
        };
        this.physBody = gPhysicsEngine.addBody(entityDef);
        this.physBody.SetLinearVelocity(new Vec2(settings.dir.x * this.speed,
                                                 settings.dir.y * this.speed));
    }