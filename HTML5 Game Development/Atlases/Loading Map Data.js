var TILEDMapClass = Class.extend({
    fullyLoaded: false,
    load: function (map) {
        xhrGet(map, function() {
            this.fullyLoaded = true;
        });
    }
});
var gMap = new TILEDMapClass();