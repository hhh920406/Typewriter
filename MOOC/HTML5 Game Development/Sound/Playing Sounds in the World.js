    playWorldSound: function (soundURL, x, y) {
        if (gGameEngine.gPlayer0 === null) return;
        var gMap = gGameEngine.gMap;
        var viewSize = Math.max(gMap.viewRect.w, gMap.viewRect.h) * 0.5;
        var oCenter = gGameEngine.gPlayer0.pos;
        var dx = oCenter.x - x;
        var dy = oCenter.y - y;
        var dist = Math.sqrt(dx * dx + dy * dy);
        var norm = dist / viewSize;
        if (norm > 1) norm = 1;
        if (norm < 0) return;
        var volume = 1.0 - norm;
        var sound = gSM.loadAsync(soundURL, function(snd) {
            gSM.playSound(snd.path, {
                looping: false,
                volume: volume
            });
        });
    }