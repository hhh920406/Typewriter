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
    imgLoadCount: 0,
    fullyLoaded: false,
    load: function (map) {
        xhrGet(map, function (data) {
            gMap.parseMapJSON(data.responseText);
        });
    },
    parseMapJSON: function (mapJSON) {
        gMap.currMapData = JSON.parse(mapJSON);
        var map = gMap.currMapData;
        gMap.numXTiles = map.width;
        gMap.numYTiles = map.height;
        gMap.tileSize.x = map.tilewidth;
        gMap.tileSize.y = map.tileheight;
        gMap.pixelSize.x = gMap.numXTiles * gMap.tileSize.x;
        gMap.pixelSize.y = gMap.numYTiles * gMap.tileSize.y;
        var total = map.tilesets.length;
        var imgOnLoad = function() {
            if (++gMap.imgLoadCount === total) {
                gMap.fullyLoaded = true;
            }
        };
        for (var i = 0; i < total; ++i) {
            var img = new Image();
            img.onload = imgOnLoad();
            img.src = map.tilesets[i].image;
        }
    }
});
var gMap = new TILEDMapClass();