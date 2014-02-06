    update: function () {
        var start = Date.now();
        gPhysicsEngine.world.Step(this.PHYSICS_LOOP_HZ, 10, 10);
        this.world.ClearForces();
        return(Date.now() - start);
    }