/* 
 * 和轮廓绘制相关的代码。
 * @author ZHG <CyberZHG@gmail.com>
 */
var wp = $("#wPaint").wPaint({
    lineWidth : '1',
    strokeStyle : '#0000FF',
    menuTitles : {
        'undo': '撤销',
        'redo': '重做',
        'clear': '清除',
        'rectangle': '矩形',
        'ellipse': '椭圆',
        'line': '直线',
        'pencil': '铅笔',
        'text': '文字',
        'eraser': '橡皮',
        'fillColor': '填充',
        'lineWidth': '线宽',
        'strokeColor': '画笔颜色',
        'bold': '粗体',
        'italic': '斜体',
        'underline': '下划线',
        'fontSize': '字体大小',
        'fontFamily': '字体类型'
    }
}).data('_wPaint');

function load_image() {
    $("#wPaint").wPaint("image", "images/demo/wPaint.png");
}

function wPaint_clear() {
    $("#wPaint").wPaint("clear");
}

function wPaint_upload() {
    $("#CheckBox_Shape").prop("checked", false);
    $("#CheckBox_Color").prop("checked", false);
    $("#CheckBox_Stripe").prop("checked", true);
    var imageData = $("#wPaint").wPaint("image");
    var formData = new FormData();
    formData.append("method", "search.image.base64");
    formData.append("image", imageData);
    $.ajax({
        url : SERVER_URL,
        type : "POST", 
        contentType: false,
        processData: false,
        data : formData,
        dataType : "json",
        timeout : 3000,
        success : function(json) {
            var condition = getCondition();
            window.location = "http://" + window.location.host + window.location.pathname + "?token=" + json.token + "&" + condition;
        }
    });
}