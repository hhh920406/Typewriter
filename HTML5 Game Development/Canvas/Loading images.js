setup = function() {
    var body = document.getElementById('body');
    var canvas = document.createElement('canvas');

    var ctx = canvas.getContext('2d');
    
    canvas.width = window.innerWidth;
    canvas.height = window.innerHeight;

    body.appendChild(canvas);

    img = new Image();
    img.onload = onImageLoad;
    img.src = "/media/img/gamedev/ralphyrobot.png";
};

onImageLoad = function(){
    console.log("Downloaded");
};
