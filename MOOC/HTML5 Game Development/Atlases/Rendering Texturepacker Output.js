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
    for (var key in gSpriteSheets)
    {
        var sheet = gSpriteSheets[key];
        var sprite = sheet.getStats(spritename);
        if (null !== sprite)
        {
            __drawSpriteInternal(sprite, sheet, posX, posY);
            break;
        }
    }
}

function __drawSpriteInternal(spt, sheet, posX, posY) {
    if (null === spt || null === sheet)
    {
        return;
    }
    ctx.drawImage(sheet.img, spt.x, spt.y, spt.w, spt.h, posX + spt.cx, posY + spt.cy, spt.w, spt.h);
}
