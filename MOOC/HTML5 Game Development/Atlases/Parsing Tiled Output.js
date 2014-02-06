var TILEDMapClass = Class.extend({
    currMapData: null,
    numXTiles: 100,
    numYTiles: 100,
    tileSize: {
        "x": 64,
        "y": 64
    },
    pixelSize: {
        "x": 64,
        "y": 64
    },
    fullyLoaded: false,
    load: function (map) {
        xhrGet(map, function (data) {
            gMap.parseMapJSON(data.responseText);
        });
    },
    parseMapJSON: function (mapJSON) {
        gMap.currMapData = JSON.parse(mapJSON);
        this.numXTiles = this.currMapData.width;
        this.numYTiles = this.currMapData.height;
        this.tileSize.x = this.currMapData.tilewidth;
        this.tileSize.y = this.currMapData.tileheight;
        this.pixelSize.x = this.tileSize.x * this.numXTiles;
        this.pixelSize.y = this.tileSize.y * this.numYTiles;
        this.fullyLoaded = true;
    }
});

var gMap = new TILEDMapClass();