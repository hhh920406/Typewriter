/**
 * 主页的脚本。
 * @author ZHG <CyberZHG@gmail.com>
 */

var thread = 0; /**控制自动加载的数量。*/

/**
 * 获取QueryString的内容。
 * @param {string} name Query string的key。
 * @returns {string} 查询结果，如果不存在返回空字符串。
 */
function getQueryString(name){
     var result = location.search.match(new RegExp("[\?\&]" + name+ "=([^\&]+)","i"));
     if(result === null || result.length < 1) {
         return "";
     }
     return result[1];
}

/**
 * 获取查询图片的地址并显示。
 * @param {string} token 传入的令牌名。
 */
function getOriginImageUrl(token) {
    $.ajax({
        url : SERVER_URL,
        type : "GET", 
        data : { 
            method : "get.image.url",
            token : token
            },
        dataType : "json",
        timeout : 3000,
        success : function(json) {
            $("#Img_Origin").prop("src", json);
        }
    });
}

/**
 * 获取商品数据并显示。
 * @param {string} items 商品的数组。
 * @param {int} index 当前商品的下标。
 */
function getResultItem(items, index) {
    if (index >= items.length) {
        -- thread;
        return;
    }
    $.ajax({
        url : SERVER_URL,
        type : "GET", 
        data : { 
            method : "get.image",
            id : items[index]
            },
        dataType : "json",
        timeout : 3000,
        success : function(json) {
            var col = 1;
            for (var i = 2; i <= 4; ++i) {
                if ($("#Div_Result_Column_" + i).prop("offsetHeight") < $("#Div_Result_Column_" + col).prop("offsetHeight")) {
                    col = i;
                }
            }
            $("#Div_Result_Column_" + col).append(
                "<div id = Result_Item_" + $("#Result_Number").val() + " class = resultItemDiv>" + 
                "<img class = resultItemImage src = " + json.image + ">" + 
                "</img>" + 
                "<div class = resultItemTitle>" + 
                "<a href = " + json.url + " target = _blank>" + json.name + "</a>" +
                "</div>" + 
                "价格：<span class = resultItemPrice>" + json.price + "</span>元" +
                "</div>"
            );
            $("#Result_Item_" + $("#Result_Number").val()).fadeIn(300);
            $("#Result_Number").val(parseInt($("#Result_Number").val()) + 1);
            getResultItem(items, parseInt(index) + 4);
        },
        error : function() {
            $("#Result_Number").val(parseInt($("#Result_Number").val()) + 1);
            getResultItem(items, parseInt(index) + 4);
        }
    });
}

/**
 * 获取查询结果并显示。
 * @param {string} token 传入的令牌名。
 */
function getResult(token) {
    var index = $("#Result_Number").val();
    $.ajax({
        url : SERVER_URL,
        type : "GET", 
        data : { 
            method : "get.image.result",
            token : token,
            index : index,
            number : 16
            },
        dataType : "json",
        timeout : 300000,
        success : function(json) {
            getResultItem(json, 0);
            getResultItem(json, 1);
            getResultItem(json, 2);
            getResultItem(json, 3);
            thread += 4;
        }
    });
}

function dropOver(event) {
    event.preventDefault();
    return true;
}

function dropImage(event) {
    event.preventDefault();
    var file = event.dataTransfer.files[0];
    var formData = new FormData();
    formData.append("method", "search.image.upload");
    formData.append("upload", file);
    $.ajax({
        url : SERVER_URL,
        type : "POST", 
        contentType: false,
        processData: false,
        data : formData,
        dataType : "json",
        timeout : 3000,
        success : function(json) {
            window.location = "http://" + window.location.host + window.location.pathname + "?token=" + json.token;
        }
    });
    /*var reader = new FileReader();
    reader.onload = function() {
        setTimeout(function(){}, 10000);
        var imageData = reader.result;
        $.ajax({
            url : SERVER_URL,
            type : "POST", 
            data : { 
                method : "search.image.upload",
                upload : imageData
            },
            dataType : "html",
            timeout : 3000,
            success : function(json) {
                alert(json);
            },
            error : function(a, b, c) {
                alert(a + b + c);
            }
        });
    };
    reader.readAsDataURL(file);*/
    return false;
}

$(function() {
    // 详细配置的显示和隐藏。
    $("#Link_Config").click(function() {
        $(".searchConfigDetailDiv").fadeToggle(300);
    });
    // 点击图片搜索按钮后触发。
    $(".searchImage").click(function() {
        $(".uploadImageDiv").fadeToggle(300);
    });
    // 切换到网上图片模式。
    $("#Link_Url").click(function() {
        $("#Div_Url").slideDown(300);
        $("#Div_Upload").slideUp(300);
    });
    // 切换到上传图片模式。
    $("#Link_Upload").click(function() {
        $("#Div_Url").slideUp(300);
        $("#Div_Upload").slideDown(300);
    });
    // 页面加载完成之后获取搜索结果。
    $(document).ready(function(){
        $("#Result_Number").val(0);
        var token = getQueryString("token");
        if (token !== "") {
            getOriginImageUrl(token);
            getResult(token);
        }
    });
    // 页面滚动到低端后获取搜索结果。
    $(window).bind("scroll", function(){
        var top = document.documentElement.scrollTop + document.body.scrollTop;
        var textheight = $(document).height();
        if (textheight - top - $(window).height() <= 100) {
            if (parseInt($("#Result_Number").val()) < 200) {
                if (thread === 0) {
                    var token = getQueryString("token");
                    if (token !== "") {
                        getResult(token);
                    }
                }
            }
        }
    });
});