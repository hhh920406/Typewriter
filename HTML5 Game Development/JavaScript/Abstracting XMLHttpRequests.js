function xhrGet(reqUri, callback, type) {
    var xhr = new XMLHttpRequest();
    xhr.open("GET", reqUri, true);
    if (type) {
        xhr.responseType = type;
    }
    xhr.onload = function() {
        if (callback) {
            try {
                callback(xhr);
            } catch(e) {
                throw e;
            }
        }
    };
    xhr.send();
}

parseJSON = function (xhr) {
    var parsedJSON = JSON.parse(xhr.responseText);
    var x = parsedJSON.frames['chaingun_impact.png'].spriteSourceSize.x;
    console.log(x);
    return x;
};

playSound = function (xhr) {
    try {
        var context = new webkitAudioContext();
        var mainNode = context.createGainNode(0);
        mainNode.connect(context.destination);
        var clip = context.createBufferSource();
        context.decodeAudioData(xhr.response, function (buffer) {
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
