Sound = Class.extend({
    path: "",
    play: function(loop) {
        gSM.playSound(this.path, {looping: loop, volume: 1});
    }
});

function playSoundInstance(soundpath) {
    var sound = gSM.loadAsync(soundpath, function(snd) {
        snd.play(false);
    });
}