    addBody: function (entityDef) {
        var bodyDef = new BodyDef();
        if (entityDef.type === 'static') {
            bodyDef.type = Body.b2_staticBody;
        } else {
            bodyDef.type = Body.b2_dynamicBody;
        }
        bodyDef.position.x = entityDef.x;
        bodyDef.position.y = entityDef.y;
        var body = this.registerBody(bodyDef);
        var fixtureDef = new FixtureDef();
        if(entityDef.useBouncyFixture) {
            fixtureDef.density = 1.0;
            fixtureDef.friction = 0;
            fixtureDef.restitution = 1.0;
        }
        var polygon = new PolygonShape();
        polygon.SetAsBox(entityDef.halfWidth, entityDef.halfHeight);
        fixtureDef.shape = polygon;
        body.CreateFixture(fixtureDef);
        return body;
    }