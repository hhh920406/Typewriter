var TILEDMapClass = Class.extend({
    currMapData: null,
    tilesets: [],
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
        for(var i = 0; i < map.tilesets.length; i++) {
            var img = new Image();
            img.onload = function () {
                gMap.imgLoadCount++;
                if (gMap.imgLoadCount === map.tilesets.length) {
                    gMap.fullyLoaded = true;
                }
            };
            img.src = map.tilesets[i].image;
            var ts = {
                "firstgid": map.tilesets[i].firstgid,
                "image": img,
                "imageheight": map.tilesets[i].imageheight,
                "imagewidth": map.tilesets[i].imagewidth,
                "name": map.tilesets[i].name,
                "numXTiles": map.tilesets[i].imagewidth / map.tilesets[i].tilewidth,
                "numYTiles": map.tilesets[i].imageheight / map.tilesets[i].tileheight
            };
            this.tilesets.push(ts);
        }
    }
});
var gMap = new TILEDMapClass();