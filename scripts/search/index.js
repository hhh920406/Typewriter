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
            token : token,
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
 * @param string itemID 商品的ID。
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
                "<div>" + json.name + "</div>" + 
                "<a href = " + json.url + ">" +
                "<img src = " + json.image + ">" + 
                "</img>" +
                "</a>" + 
                "<div class = resultItemPrice>" + "￥" + json.price + "</div>" +
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
    $(document).ready(function(){
        $("#Result_Number").val(0);
        var token = getQueryString("token");
        if (token !== null) {
            getOriginImageUrl(token);
            getResult(token);
        }
    });
    $(window).bind("scroll", function(){
        var top = document.documentElement.scrollTop + document.body.scrollTop;
        var textheight = $(document).height();
        if (textheight - top - $(window).height() <= 100) {
            if (parseInt($("#Result_Number").val()) < 200) {
                if (thread == 0) {
                    var token = getQueryString("token");
                    getResult(token);
                }
            }
        }
    });
});