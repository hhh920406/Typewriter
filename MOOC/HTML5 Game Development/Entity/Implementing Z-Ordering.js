    draw: function () {
        gMap.draw(null);
        var fudgeVariance = 128;
        var zIndex_array = [];
        var entities_bucketed_by_zIndex = {};
        gGameEngine.entities.forEach(function(entity) {
            if (entity.pos.x >= gMap.viewRect.x - fudgeVariance &&
                entity.pos.x < gMap.viewRect.x + gMap.viewRect.w + fudgeVariance &&
                entity.pos.y >= gMap.viewRect.y - fudgeVariance &&
                entity.pos.y < gMap.viewRect.y + gMap.viewRect.h + fudgeVariance) {
                if (zIndex_array.indexOf(entity.zIndex) === -1) {
                    zIndex_array.push(entity.zIndex);
                    entities_bucketed_by_zIndex[entity.zIndex] = [];
                }
                entities_bucketed_by_zIndex[entity.zIndex].push(entity);
            }
        });
        zIndex_array.sort(function(a, b) {return a - b;});
        zIndex_array.forEach(function(zIndex) {
            entities_bucketed_by_zIndex[zIndex].forEach(function(entity) {
                entity.draw(fractionOfNextPhsicsUpdate);
            });
        });
    },