var setup = function() {
    var soundRequest = new XMLHttpRequest();
    soundRequest.open("GET", "/media/audio/gamedev/bg_menu.ogg", true);
    soundRequest.responseType = 'arraybuffer';
    soundRequest.onload = function () {
        try {
            var context = new webkitAudioContext();
            var mainNode = context.createGainNode(0);
            mainNode.connect(context.destination);
            var clip = context.createBufferSource();
            context.decodeAudioData(soundRequest.response, function (buffer) {
                clip.buffer = buffer;
                clip.gain.value = 1.0;
                clip.connect(mainNode);
                clip.loop = true;
                clip.noteOn(0);
            }, function (data) {});
        }
        catch(e) {
            console.warn('Web Audio API is not supported in this browser');
        }
    };
    soundRequest.send();
};
