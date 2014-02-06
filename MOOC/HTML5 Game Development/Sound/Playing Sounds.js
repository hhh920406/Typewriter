    playSound: function (path, settings) {
        if (!gSM.enabled) return false;
        var looping = false;
        var volume = 0.2;
        if (settings) {
            if (settings.looping) looping = settings.looping;
            if (settings.volume) volume = settings.volume;
        }
        var sd = this.clips[path];
        if (sd === null) return false;
        if (sd.l === false) return false;
        var currentClip = gSM._context.createBufferSource();
        currentClip.buffer = sd.b;
        currentClip.gain.value = volume;
        currentClip.loop = looping;
        currentClip.connect(gSM._mainNode);
        currentClip.noteOn(0);
        return true;
    }