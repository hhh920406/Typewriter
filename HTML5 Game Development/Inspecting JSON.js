parseJSON = function (weaponJSON) {
    var data = JSON.parse(weaponJSON);
    return data.frames['chaingun_impact.png'].spriteSourceSize.x;
};