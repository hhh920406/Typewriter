/**
 * 主页的脚本。
 * @author ZHG <CyberZHG@gmail.com>
 */

/**
 * 检测是否至少选中了一个相册。
 * @returns {Boolean} 如果至少选中了一个相册则返回true，否则返回false。
 */
function check() {
    var flag = false;
    $(function(){
        $("input:checkbox").each(function() {
            if($(this).prop("checked")) {
                flag = true;
            }
        });
    });
    if (flag) {
        $(".selectBlock").slideDown(500);
    } else {
        $(".selectBlock").slideUp(500);
    }
    return flag;
}
check();

/**
 * 恢复最初的样式。
 */
function restore() {
    $(".resultBlock").slideUp(500, function() {
        $(".processBlock").slideUp(500, function() {
            $(".albumBlock").slideDown(500, function() {
                check();
                $("#Button_Save").fadeOut();
                $("#Div_Process").html("");
                $("#Div_Result").html("");
                $(".cookieBlock").html("");
            });
        });
    });
}

/**
 * 进入处理阶段。
 */
function showProcessBlock() {
    $(".albumBlock").slideUp(300,function() {
        $(".selectBlock").slideUp(300, function() {
            $(".processBlock").slideDown(500, function() {
                $(".resultBlock").slideDown(500);
            });
        });
    });
}

/**
 * 记录数据。
 * @param {string} key 
 * @param {string} value
 */
function setValue(key, value) {
    if ($("#cookie_" + key).length === 0) {
        $(".cookieBlock").append("<input type = hidden id = 'cookie_" + key + "' value = '" + value + "'/>");
    } else {
        $("#cookie_" + key).val(value);
    }
}

/**
 * 读取数据。
 * @param {string} key
 * @returns {string} value
 */
function getValue(key) {
    return $("#cookie_" + key).val();
}

/**
 * 将当前选择的相册列表记入到Cookie中。
 */
function recordSelection() {
    var count = 0;
    $("input:checkbox").each(function() {
        if ($(this).prop("checked")) {
            var name = $(this).next("span").text();
            var id = $(this).val();
            setValue("clarify_album_name_" + count, name);
            setValue("clarify_album_id_" + count, id);
            ++ count;
        }
    });
    setValue("clarify_album_count", count);
    setValue("clarify_date_time", (new Date()).toLocaleString());
    setValue("clarify_result_count", 0);;
}

/**
 * 保存并显示照片分类结果。
 * @param {int} photoIndex 当前照片的索引。
 * @param {string} category 类别。
 */
function savePhotoClarifyResult(photoIndex, category) {
    var date = getValue("clarify_date_time");
    var id = getValue("clarify_photo_id_" + photoIndex);
    var url = getValue("clarify_photo_url_" + photoIndex);
    var albumID = "Result_" + category;
    var albumName = category + " " + date;
    if ($("#" + albumID).length === 0) {
        var count = parseInt(getValue("clarify_result_count"));
        $("#Div_Result").append("<div id = '" + albumID + "' name = '" + count + "' class = 'resultBlockItem'></div");
        setValue("clarify_result_" + count + "_count", 0);
        setValue("clarify_result_" + count + "_name", albumName);
        setValue("clarify_result_count", count + 1);
    }
    var index = $("#" + albumID).attr("name");
    var count = parseInt(getValue("clarify_result_" + index + "_count"));
    setValue("clarify_result_" + index + "_id_" + count, id);
    setValue("clarify_result_" + index + "_count", count + 1);
    var imgHTML = "<div class = 'selectBlockItemImageDiv'><img src = " + url + " alt = " + url + "></img></div>";
    var checkboxHTML = "<div class = 'selectBlockItemInputDiv'><input type = checkbox name = 'Checkbox_Result' value = " + index + ">" + albumName + "</input></div>";
    $("#" + albumID).html(imgHTML + checkboxHTML);
}

/**
 * 对图片进行分类。
 * @param {string} pageURL 用户分类请求的网址。
 * @param {int} albumIndex 当前相册的索引。
 * @param {int} photoIndex 当前照片的索引。
 * @param {function} callback 回调函数。
 */
function clarifyPhoto(pageURL, albumIndex, photoIndex, callback) {
    if (photoIndex < getValue("clarify_photo_count")) {
        var id = getValue("clarify_photo_id_" + photoIndex);
        var url = getValue("clarify_photo_url_" + photoIndex);
        url = encodeURIComponent(url);
        $.ajax({
            url : pageURL,
            type : "GET", 
            data : {
                photoid : id,
                photourl : url
            },
            dataType : "html",
            timeout : 180000,
            success : function(html) {
                var name = getValue("clarify_album_name_" + albumIndex);
                var number = getValue("clarify_photo_count");
                $(".current").html(name + " [" + (photoIndex + 1) + "/" + number + "]");
                if ("" !== html) {
                    savePhotoClarifyResult(photoIndex, html);
                }
                clarifyPhoto(pageURL, albumIndex, photoIndex + 1, callback);
            },
            error : function() {
                var name = getValue("clarify_album_name_" + albumIndex);
                var number = getValue("clarify_photo_count");
                $(".current").html(name + " [" + (photoIndex + 1) + "/" + number + "]");
                clarifyPhoto(pageURL, albumIndex, photoIndex + 1, callback);
            }
        });
    } else {
        callback(pageURL, albumIndex + 1);
    }
}

/**
 * 对相册进行分类。
 * @param {string} pageURL 用户分类请求的网址。
 * @param {int} albumIndex 当前相册的索引。
 */
function clarifyAlbum(pageURL, albumIndex) {
    $(".current").attr("class", "history");
    if (albumIndex < getValue("clarify_album_count")) {
        var name = getValue("clarify_album_name_" + albumIndex);
        var id = getValue("clarify_album_id_" + albumIndex);
        $("#Div_Process").append("<div class = 'current'></li>");
        $.ajax({
            url : "ajax_get_photos.php",
            type : "GET", 
            data : {albumid : id},
            dataType : "json",
            timeout : 5000,
            success : function(json) {
                var count = 0;
                $.each(json, function(index) {
                    setValue("clarify_photo_id_" + count, json[index].PhotoID);
                    setValue("clarify_photo_url_" + count, json[index].PhotoPath);
                    ++ count;
                });
                setValue("clarify_photo_count", count);
                $(".current").html(name + " [0/" + count + "]");
                clarifyPhoto(pageURL, albumIndex, 0, clarifyAlbum);
            },
            error : function() {
                $(".current").html(name + " [0/0]");
                clarifyAlbum(pageURL, albumIndex + 1);
            }
        });
    } else {
        $(".processBlock").slideUp(800, function() {
            $("#Button_Save").fadeIn(500);
        });
    }
}

/**
 * 保存分类的结果到服务器上。
 * @param {int} resultIndex 结果的索引。
 */
function saveClarifyResult(resultIndex) {
    var name = getValue("clarify_result_" + resultIndex + "_name");
    var count = getValue("clarify_result_" + resultIndex + "_count");
    var list = "";
    for (var i = 0; i < count; ++ i) {
        if (i) {
            list += ",";
        }
        list += getValue("clarify_result_" + resultIndex + "_id_" + i);
    }
    $.ajax({
        url : "ajax_save_result.php",
        type : "POST", 
        data : {name : name, list : list},
        dataType : "html",
        timeout : 180000,
        async : false
    });
}

$(function() {
    /**
     * 选择全部相册。
     */
    $("#Select_All").click(function() {
        $("input:checkbox").prop("checked", true);
        check();
    });
    
    /**
     * 取消选择全选相册。
     */
    $("#Select_None").click(function() {
        $("input:checkbox").prop("checked", false);
        check();
    });
    
    /**
     * 反选相册。
     */
    $("#Select_Reverse").click(function() {
        $("input:checkbox").each(function() {
            if ($(this).prop("checked")) {
                $(this).prop("checked", false);
            } else {
                $(this).prop("checked", true);
            }
        });
        check();
    });
    
    /**
     * Checkbox状态发生变化。
     */
    $("input:checkbox").click(function() {
        check();
    });
    
    /**
     * 对颜色进行分类。
     */
    $("#Link_Color").click(function() {
        showProcessBlock();
        recordSelection();
        clarifyAlbum("ajax_clarify_color.php", 0);
    });
    
    /**
     * 对时间进行分类。
     */
    $("#Link_Time").click(function() {
        showProcessBlock();
        recordSelection();
        clarifyAlbum("ajax_clarify_time.php", 0);
    });
    
    /**
     * 对事件进行分类。
     */
    $("#Link_Event").click(function() {
        showProcessBlock();
        recordSelection();
        clarifyAlbum("ajax_clarify_event.php", 0);
    });
    
    /**
     * 取消分类。
     */
    $("#Button_Cancel").click(function() {
        setValue("clarify_album_count", 0);
        setValue("clarify_photo_count", 0);
        restore();
    });
    
    /**
     * 保存分类结果。
     */
    $("#Button_Save").click(function() {
        $("#Button_Save").prop("disabled", true);
        $("input[name='Checkbox_Result']").each(function() {
            if ($(this).prop("checked")) {
                $(this).prop("checked", false);
                $(this).prop("disabled", true);
                saveClarifyResult($(this).val());
                $(this).parent().parent().fadeOut(500);
            }
        });
        $("#Button_Save").prop("disabled", false);
    });
});