SoundManager = Class.extend({
    clips: {},
    enabled: true,
    _context: null,
    _mainNode: null,
    create: function () {
        try {
            this._context = new webkitAudioContext();
        } catch (e) {
            window.alert("Uncompatibility");
        }
        this._mainNode = this._context.createGainNode();
        this._context.destination = this._mainNode.connect(this._mainNode);
    }
});

var gSM = new SoundManager();