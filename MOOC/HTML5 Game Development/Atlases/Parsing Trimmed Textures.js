var gSpriteSheets = {};

SpriteSheetClass = Class.extend({
    img: null,
    url: "",
    sprites: [],
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
            "cx": cx === null ? 0 : cx,
            "cy": cy === null ? 0 : cy
        };
        this.sprites.push(spt);
    },
    parseAtlasDefinition: function (atlasJSON) {
        var parsed = JSON.parse(atlasJSON);
        for(var key in parsed.frames) {
            var sprite = parsed.frames[key];
            var cx = -sprite.frame.w * 0.5;
            var cy = -sprite.frame.h * 0.5;
            if (sprite.trimmed) {
                cx = sprite.spriteSourceSize.x - (sprite.sourceSize.w * 0.5);
                cy = sprite.spriteSourceSize.y - (sprite.sourceSize.h * 0.5);
            }
            this.defSprite(key, sprite.frame.x, sprite.frame.y, sprite.frame.w, sprite.frame.h, cx, cy);
        }
    },
    getStats: function (name) {
        for(var i = 0; i < this.sprites.length; i++) {
            if(this.sprites[i].id === name) {
                return this.sprites[i];
            }
        }
        return null;
    }

});

function drawSprite(spritename, posX, posY) {
    for(var sheetName in gSpriteSheets) {
        var sheet = gSpriteSheets[sheetName];
        var sprite = sheet.getStats(spritename);
        if(sprite === null) {
            continue;
        }
        __drawSpriteInternal(sprite, sheet, posX, posY);
        return;
    }
}

function __drawSpriteInternal(spt, sheet, posX, posY) {
    if (spt === null || sheet === null) {
        return;
    }
    var hlf = {
        x: spt.cx,
        y: spt.cy
    };
    ctx.drawImage(sheet.img, spt.x, spt.y, spt.w, spt.h, posX + hlf.x, posY + hlf.y, spt.w, spt.h);
}
