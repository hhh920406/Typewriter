GameEngineClass = Class.extend({
    move_dir: new Vec2(0,0),
    dirVec: new Vec2(0,0),
    gPlayer0: {
        pos: {
            x: 100,
            y: 100
        },
        walkSpeed: 1,
        mpPhysBody: new BodyDef()
    },
    setup: function () {
        gInputEngine.setup();
    },
    update: function () {
        if (gInputEngine.actions['move-up']) {
            gGameEngine.move_dir.y -= 1;
        }
        if (gInputEngine.actions['move-down']) {
            gGameEngine.move_dir.y += 1;
        }
        if (gInputEngine.actions['move-left']) {
            gGameEngine.move_dir.x -= 1;
        }
        if (gInputEngine.actions['move-right']) {
            gGameEngine.move_dir.x += 1;
        }
        if (gGameEngine.move_dir.LengthSquared()) {
            gGameEngine.move_dir.Normalize();
            gGameEngine.move_dir.Multiply(gGameEngine.gPlayer0.walkSpeed);
        }
        gGameEngine.gPlayer0.mpPhysBody.setLinearVelocity(gGameEngine.move_dir.x, gGameEngine.move_dir.y);
        if (gInputEngine.actions.fire0 || gInputEngine.actions.fire1) {
        }
    }
});
gGameEngine = new GameEngineClass();