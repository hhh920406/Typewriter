var manipulateDOM = function() {
    var div = document.createElement('div');
    div.id = 'gameContent';
    var canvas = document.createElement('canvas');
    canvas.id = 'gameCanvas';
    div.appendChild(canvas);
    document.body.appendChild(div);
};
