SoundManager = Class.extend({
    clips: {},
    enabled: true,
    _context: null,
    _mainNode: null,
    create: function () {
        try {
            this._context = new webkitAudioContext();
        } catch (e) {
            alert('Web Audio API is not supported in this browser');
        }

        this._mainNode = this._context.createGainNode(0);
        this._mainNode.connect(this._context.destination);
    },
    loadAsync: function (path, callbackFcn) {
        if(gSM.clips[path]){
            callbackFcn(gSM.clips[path].s);
            return gSM.clips[path].s;
        }
        var clip = {s:new Sound(),b:null,l:true};
        gSM.clips[path] = clip;
        clip.s.path = path;
        var xhr = new XMLHttpRequest();
        xhr.open('GET', path, true);
        xhr.responseType = 'arraybuffer';        
        xhr.onload = function(){
            gSM._context.decodeAudioData(xhr.response,
                function(buffer){
                    clip.b = buffer;
                    clip.l = true;
                    callbackFcn(clip.s);
                },
                function(data){
                    Logger.log("failed");
                }
            );
        };
        xhr.send();
        return new Sound(clip.s);
    }
});
Sound = Class.extend({});
var gSM = new SoundManager();