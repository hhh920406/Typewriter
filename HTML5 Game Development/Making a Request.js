parseJSON = function (weaponJSON) {
    var parsedJSON = JSON.parse(weaponJSON);
    return parsedJSON.frames['chaingun_impact.png'].spriteSourceSize.x;
};

var setup = function() {
    var xhr = new XMLHttpRequest();
    xhr.open("GET", "/media/resources/gamedev/weapon.json", true);
    xhr.onload = function () {
        console.log(parseJSON(this.responseText));
    };
    xhr.send();
};
