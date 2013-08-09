var canvas = null;
var ctx = null;
var img = null;

var onImageLoad = function() {
    ctx.drawImage(img, 192, 192);
};

var setup = function() {
    var body = document.getElementById("body");
    canvas = document.createElement("canvas");

    ctx = canvas.getContext('2d');

    canvas.setAttribute('width', 500);
    canvas.setAttribute('height', 700);

    body.appendChild(canvas);

    img = new Image();
    img.onload = onImageLoad;
    img.src = "/media/img/gamedev/ralphyrobot.png";
};
