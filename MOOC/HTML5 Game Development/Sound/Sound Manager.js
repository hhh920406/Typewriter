SoundManager = Class.extend({
    clips : {},
    enabled : true, 
    _context : null,
    _mainNode : null
});

var gSM = new SoundManager();