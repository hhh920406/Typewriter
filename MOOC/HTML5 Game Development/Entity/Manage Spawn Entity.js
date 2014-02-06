    spawnEntity: function (typename) {
        switch (typename) {
        case "Player":
            return new PlayerClass();
        case "Landmine":
            return new LandmineClass();
        case "QuadDamage":
            return new QuadDamageClass();
        }
        return null;
    }