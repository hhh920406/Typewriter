var gSpriteSheets = {};
SpriteSheetClass = Class.extend({
    img: null,
    url: "",
    sprites: new Array(),
    init: function () {},
    load: function (imgName) {
        this.url = imgName;
        var img = new Image();
        img.src = imgName;
        this.img = img;
        gSpriteSheets[imgName] = this;
    },
    defSprite: function (name, x, y, w, h, cx, cy) {
        var spt = {
            "id": name,
            "x": x,
            "y": y,
            "w": w,
            "h": h,
            "cx": cx == null ? 0 : cx,
            "cy": cy == null ? 0 : cy
        };
        this.sprites.push(spt);
    },
    parseAtlasDefinition: function (atlasJSON) {
        var atlasInfo = JSON.parse(atlasJSON);
        for (var name in atlasInfo.frames) {
            var item = atlasInfo.frames[name];
            var x = item.frame.x;
            var y = item.frame.y;
            var w = item.frame.w;
            var h = item.frame.h;
            var cx = - w * 0.5;
            var cy = - h * 0.5;
            this.defSprite(name, x, y, w, h, cx, cy);
        }
    }
});

