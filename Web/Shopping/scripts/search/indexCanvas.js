/**
 * 绘制喜好设置的界面。
 * @author ZHG <CyberZHG@gmail.com>
 */
onload = function() {
    draw();
};

var preferColorX = 100;
var preferColorY = 20;
var preferShapeX = 3;
var preferShapeY;
var preferStripeX;
var preferStripeY;

/**
 * Canvas的绘制。
 * @returns {Boolean} 如果可以绘制返回true，否则返回false。
 */
function draw() {
    var canvas = document.getElementById("Canvas_Prefer");
    if (! canvas || !canvas.getContext) {
        return false;
    }
    var context = canvas.getContext("2d");
    context.font ="15px Times New Roman";
    context.fillText("颜色", 110, 15);
    context.fillText("形状", 0, 175);
    context.fillText("纹理", 170, 175);
    context.fillStyle = "rgb(240, 240, 240)";
    context.strokeStyle = "rgb(200, 200, 200)";
    
    context.beginPath();
    context.moveTo(100, 107);
    context.lineTo(100, 10);
    context.lineTo(190, 155);
    context.closePath();
    context.fill();
    context.stroke();
    
    context.beginPath();
    context.moveTo(100, 107);
    context.lineTo(190, 155);
    context.lineTo(10, 155);
    context.closePath();
    context.fill();
    context.stroke();
    
    context.beginPath();
    context.moveTo(100, 107);
    context.lineTo(10, 155);
    context.lineTo(100, 10);
    context.closePath();
    context.fill();
    context.stroke();
    return true;
}
