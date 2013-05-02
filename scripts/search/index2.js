/**
 * 主页的脚本。
 * @author ZHG <CyberZHG@gmail.com>
 */

var thread = 0; /**控制自动加载的数量。*/
var columnNum = 1; /** 显示列的数量。 */

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
        timeout : 5000,
        success : function(json) {
            var col = 0;
            for (var i = 1; i < columnNum; ++i) {
                if ($("#Div_Result_Column_" + i).prop("offsetHeight") < $("#Div_Result_Column_" + col).prop("offsetHeight")) {
                    col = i;
                }
            }
            try {
                $("#Div_Result_Column_" + col).append(
                    "<div id = Result_Item_" + $("#Result_Number").val() + " class = resultItemDiv>" + 
                    "<img class = resultItemImage src = " + json.image + " onclick = showImage('" + json.image + "');>" + 
                    "</img>" + 
                    "<div class = resultItemTitle>" + 
                    "<a href = " + json.url + " target = _blank>" + json.name + "</a>" +
                    "</div>" + 
                    "价格：<span class = resultItemPrice>" + json.price + "</span>元" +
                    "</div>"
                );
                $("#Result_Item_" + $("#Result_Number").val()).fadeIn(300);
                $("#Result_Number").val(parseInt($("#Result_Number").val()) + 1);
            } catch (err) {
            }
            getResultItem(items, parseInt(index) + 5);
        },
        error : function() {
            $("#Result_Number").val(parseInt($("#Result_Number").val()) + 1);
            getResultItem(items, parseInt(index) + 5);
        }
    });
}

var querying = false;

/**
 * 获取查询结果并显示。
 * @param {string} token 传入的令牌名。
 */
function getResult(token) {
    if (querying) {
        return;
    }
    querying = true;
    columnNum = parseInt(($(window).width() - $(".searchConfigDetailDiv").width() - 20) / ($("#Div_Result_Column_0").width() + 10));
    for (var i = 1; i < columnNum; ++i) {
        $(".resultDiv").append("<div id = Div_Result_Column_" + i + " class = resultColumnDiv></div>");
    }
    $(".resultDiv").css("width", $(window).width());
    var index = $("#Result_Number").val();
    var data = { 
        method : "get.image.result",
        token : token,
        index : index,
        number : 16
    };
    if (getQueryString("start_price") !== "" && getQueryString("end_price") !== "") {
        data.start_price = getQueryString("start_price");
        data.end_price = getQueryString("end_price");
    }
    if (getQueryString("seller") !== "") {
        data.seller = getQueryString("seller");
    }
    if (getQueryString("category") !== "") {
        data.category = getQueryString("category");
    }
    if (getQueryString("prefer") !== "") {
        data.prefer = getQueryString("prefer");
    }
    $.ajax({ 
        url : SERVER_URL,
        type : "GET", 
        data : data,
        dataType : "json",
        timeout : 300000,
        success : function(json) {
            getResultItem(json, 0);
            getResultItem(json, 1);
            getResultItem(json, 2);
            getResultItem(json, 3);
            getResultItem(json, 4);
            thread += 5;
            querying = false;
        },
        error : function(a, b, c) {
            //alert(a + b + c);
        }
    });
}

function dropOver(event) {
    event.preventDefault();
    return true;
}

function getPreferString() {
    var condition = "";
    if ($("#CheckBox_Shape").prop("checked")) {
        condition += "1";
    } else {
        condition += "0";
    }
    if ($("#CheckBox_Color").prop("checked")) {
        condition += "1";
    } else {
        condition += "0";
    }
    if ($("#CheckBox_Stripe").prop("checked")) {
        condition += "1";
    } else {
        condition += "0";
    }
    return condition;
}

/**
 * 获取搜索的条件。
 * @return {string} QueryString形式的条件。
 */
function getCondition() {
    var flag = false;
    var condition = "";
    var startPrice = parseInt($("#Input_Price_Start").val());
    var endPrice = parseInt($("#Input_Price_End").val());
    if (!isNaN(startPrice)) {
        if (flag) {
            condition += "&";
        } else {
            flag = true;
        }
        condition += "start_price=" + startPrice;
    }
    if (!isNaN(endPrice)) {
        if (flag) {
            condition += "&";
        } else {
            flag = true;
        }
        condition += "&end_price=" + endPrice;
    }
    if ($("#Select_Seller").val().length > 0) {
        if (flag) {
            condition += "&";
        } else {
            flag = true;
        }
        condition += "seller=" + encodeURI($("#Select_Seller").val());
    }
    if ($("#Select_Category").val() !== "null") {
        if (flag) {
            condition += "&";
        } else {
            flag = true;
        }
        condition += "category=" + encodeURI($("#Select_Category").val());
    }
    if (flag) {
        condition += "&";
    } else {
        flag = true;
    }
    condition += "prefer=" + getPreferString();
    return condition;
}

function showImage(imageUrl) {
    $("#Div_Show_Image").css("left", "0");
    $("#Div_Show_Image").css("top", "0");
    $("#Div_Show_Image").width(10000);
    $("#Div_Show_Image").height(10000);
    $("#Img_Show").prop("src", imageUrl);
    $("#Div_Show_Image").fadeIn(600);
    $("#Div_Show_Back").fadeIn(300, function() {
    });
    $("#Img_Show").load(function() {
        $("#Div_Show_Image").width($("#Img_Show").width());
        $("#Div_Show_Image").height($("#Img_Show").height());
        $("#Div_Show_Image").css("left", (($(window).width() - $("#Img_Show").width()) / 2) + "px");
        $("#Div_Show_Image").css("top", (($(window).height() - $("#Img_Show").height()) / 2) + "px");
    });
}

/**
 * 从Query String中获取条件信息。
 */
function loadCondition() {
    var value = getQueryString("start_price");
    if (value !== "") {
        $("#Input_Price_Start").val(value);
    }
    value = getQueryString("end_price");
    if (value !== "") {
        $("#Input_Price_End").val(value);
    }
    value = getQueryString("keyword");
    if (value !== "") {
        $("#Input_Keyword").val(decodeURI(value));
    }
    value = getQueryString("prefer");
    if (value === "") {
        $("#CheckBox_Shape").prop("checked", true);
        $("#CheckBox_Color").prop("checked", false);
        $("#CheckBox_Stripe").prop("checked", false);
    } else {
        $("#CheckBox_Shape").prop("checked", value[0] === "1");
        $("#CheckBox_Color").prop("checked", value[1] === "1");
        $("#CheckBox_Stripe").prop("checked", value[2] === "1");
    }
}

function getSeller() {
    $.ajax({
        url : SERVER_URL,
        type : "GET", 
        data : {method : "get.seller.list"},
        dataType : "json",
        timeout : 10000,
        success : function(json) {
            for (var i = 0; i < json.length; ++i) {
                $("#Select_Seller").append("<option value = " + json[i].id + ">" + json[i].name + "</option>");
            }
            var value = getQueryString("seller");
            if (value !== "") {
                $("#Select_Seller option[value=" + value + "]").attr("selected","true");
            }
        },
        error : function(a, b, c) {
            alert("Seller Error: " + a + " / " + b + " / " + c);
        }
    });
}

/**
 * 获取分类信息。
 */
function getCategory() {
    $.ajax({
        url : SERVER_URL,
        type : "GET", 
        data : {method : "get.category.list"},
        dataType : "json",
        timeout : 10000,
        success : function(json) {
            for (var i = 0; i < json.length; ++i) {
                $("#Select_Category").append("<option value = " + json[i].id + ">" + json[i].name + "</option>");
            }
            var value = getQueryString("category");
            if (value !== "") {
                $("#Select_Category option[value=" + value + "]").attr("selected","true");
            }
        },
        error : function(a, b, c) {
            alert("Categroy Error: " + a + " / " + b + " / " + c);
        }
    });
}

function uploadImage(file) {
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
        timeout : 10000,
        success : function(json) {
            var condition = getCondition();
            window.location = "http://" + window.location.host + window.location.pathname + "?token=" + json.token + "&" + condition;
        }
    });
}

/**
 * 拖放图像的处理。
 * @param {type} event
 */
function dropImage(event) {
    event.preventDefault();
    var file = event.dataTransfer.files[0];
    uploadImage(file);
    return false;
}

function uploadWithUrl() {
    var formData = new FormData();
    formData.append("method", "search.image.website");
    formData.append("website", $("#Text_Url").val());
    $.ajax({
        url : SERVER_URL,
        type : "POST", 
        contentType: false,
        processData: false,
        data : formData,
        dataType : "json",
        timeout : 10000,
        success : function(json) {
            var condition = getCondition();
            window.location = "http://" + window.location.host + window.location.pathname + "?token=" + json.token + "&" + condition;
        }
    });
}

function uploadWithFile() {
    var file = File_Upload.files[0];
    uploadImage(file);
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
        $("#Div_Sketch").slideUp(300);
    });
    // 切换到上传图片模式。
    $("#Link_Upload").click(function() {
        $("#Div_Url").slideUp(300);
        $("#Div_Upload").slideDown(300);
        $("#Div_Sketch").slideUp(300);
    });
    $("#Link_Sketch").click(function() {
        $("#Div_Url").slideUp(300);
        $("#Div_Upload").slideUp(300);
        $("#Div_Sketch").slideDown(300);
    });
    // 页面加载完成之后获取搜索结果。
    $(document).ready(function(){
        $("#Result_Number").val(0);
        var token = getQueryString("token");
        if (token !== "") {
            getOriginImageUrl(token);
            getResult(token);
        }
        loadCondition();
        getSeller();
        getCategory();
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
    $("#Div_Show_Back").click(function() {
        $("#Div_Show_Image").fadeOut(300, function() {
            $("#Div_Show_Back").fadeOut(400);
        });
    });
    $("#Div_Show_Image").click(function() {
        $("#Div_Show_Image").fadeOut(300, function() {
            $("#Div_Show_Back").fadeOut(400);
        });
    });
    $("#Input_Type").change(function() {
        if ($("#Input_Type").val().length > 0) {
            $("#Select_Type").prop("disabled", true);
        } else {
            $("#Select_Type").prop("disabled", false);
        }
    });
    $("#Button_Search").click(function() {
        var condition = getCondition();
        var token = getQueryString("token");
        if (token !== "") {
            window.location = "http://" + window.location.host + window.location.pathname + "?token=" + token + "&" + condition;
        }
    });
    $("#Button_Url").click(function() {
        uploadWithUrl();
    });
    $("#File_Upload").change(function() {
        uploadWithFile();
    });
    $("#Button_Sketch").click(function() {
        window.location = "wpaint/wpaint.html";
    });
});