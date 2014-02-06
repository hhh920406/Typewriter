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
                "firstgid": gMap.currMapData.tilesets[i].firstgid,
                "image": img,
                "imageheight": gMap.currMapData.tilesets[i].imageheight,
                "imagewidth": gMap.currMapData.tilesets[i].imagewidth,
                "name": gMap.currMapData.tilesets[i].name,
                "numXTiles": Math.floor(gMap.currMapData.tilesets[i].imagewidth / gMap.tileSize.x),
                "numYTiles": Math.floor(gMap.currMapData.tilesets[i].imageheight / gMap.tileSize.y)
            };
            gMap.tilesets.push(ts);
        }
    },
    getTilePacket: function (tileIndex) {
        var pkt = {
            "img": null,
            "px": 0,
            "py": 0
        };
        var tile = 0;
        for(tile = gMap.tilesets.length - 1; tile >= 0; tile--) {
            if(gMap.tilesets[tile].firstgid <= tileIndex) break;
        }
        pkt.img = gMap.tilesets[tile].image;
        var localIdx = tileIndex - gMap.tilesets[tile].firstgid;
        var lTileX = Math.floor(localIdx % gMap.tilesets[tile].numXTiles);
        var lTileY = Math.floor(localIdx / gMap.tilesets[tile].numXTiles);
        pkt.px = (lTileX * gMap.tileSize.x);
        pkt.py = (lTileY * gMap.tileSize.y);


        return pkt;
    },
    draw: function (ctx) {
        if(!gMap.fullyLoaded) return;
        for (var i = 0; i < this.currMapData.layers.length; ++i) {
            if ("tilelayer" === this.currMapData.layers[i].type) {
                var data = this.currMapData.layers[i].data;
                for (var j = 0; j < data.length; ++j) {
                    if (0 !== data[j]) {
                        this.getTilePacket(data[j]);
                    }
                }
            }
        }
    }
});
var gMap = new TILEDMapClass();