    setup: function () {
        gPhysicsEngine.create();
        gPhysicsEngine.addContactListener({
            PostSolve: function (bodyA, bodyB, impulse) {
                var userA = bodyA.GetUserData();
                var userB = bodyB.GetUserData();
                userA.ent.onTouch(bodyB, null, impulse);
                userB.ent.onTouch(bodyA, null, impulse);
            }
        });