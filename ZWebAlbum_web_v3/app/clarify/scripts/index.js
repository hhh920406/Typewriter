/**
 * 主页的脚本。
 * 对于使用的Cookie的说明：
 * clarify_date_time 分类开始的时间。
 * clarify_album_count 记录相册的数量。
 * clarify_album_id_* 记录相册的ID。
 * clarify_album_name_* 记录相册的名称。
 * clarify_photo_count 记录相册中照片的数量。
 * clarify_photo_id_* 记录照片的ID。
 * clarify_photo_url_* 记录照片的路径。
 * clarify_result_count 分类后相册的数量。
 * clarify_result_*_count 分类后相册中照片的数量。
 * clarify_result_*_id_* 分类后相册中照片的ID。
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
                $("#Div_Process").html("");
                $("#Div_Result").html("");
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
 * 将当前选择的相册列表记入到Cookie中。
 */
function recordSelection() {
    var count = 0;
    $("input:checkbox").each(function() {
        if ($(this).prop("checked")) {
            var name = $(this).next("span").text();
            var id = $(this).val();
            $.cookie("clarify_album_name_" + count, name, {expires : 1, path : "/"});
            $.cookie("clarify_album_id_" + count, id, {expires : 1, path : "/"});
            ++ count;
        }
    });
    $.cookie("clarify_album_count", count, {expires: 1, path : "/"});
    $.cookie("clarify_date_time", (new Date()).toUTCString(), {expires: 1, path : "/"});
    $.cookie("clarify_result_count", 0,  {expires: 1, path : "/"});
}

/**
 * 保存并显示照片分类结果。
 * @param {int} photoIndex 当前照片的索引。
 * @param {string} category 类别。
 */
function savePhotoClarifyResult(photoIndex, category) {
    var id = $.cookie("clarify_photo_id_" + photoIndex);
    var url = $.cookie("clarify_photo_url_" + photoIndex);
    var albumID = "Result_" + category;
    if ($("#" + albumID).length === 0) {
        var count = $.cookie("clarify_result_count");
        $("#Div_Result").append("<div id = '" + albumID + "' name = '" + count + "' class = 'resultBlockItem'></div");
        $.cookie("clarify_result_" + count + "_count", 0, {expires: 1, path : "/"});
        $.cookie("clarify_result_count", count + 1, {expires: 1, path : "/"});
    }
    var index = $("#" + albumID).prop("name");
    var count = $.cookie("clarify_result_" + index + "_count");
    $.cookie("clarify_result_" + index + "_id_" + count, id, {expires: 1, path : "/"});
    $.cookie("clarify_result_" + index + "_count", count + 1, {expires: 1, path : "/"});
    var date = $.cookie("clarify_date_time");
    var imgHTML = "<div class = 'selectBlockItemImageDiv'><img src = " + url + " alt = " + url + "></img></div>";
    var checkboxHTML = "<div class = 'selectBlockItemInputDiv'><input type = checkbox name = 'Checkbox_Result' value = " + index + ">" + category + " " + date + "</input></div>";
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
    if (photoIndex < $.cookie("clarify_photo_count")) {
        var id = $.cookie("clarify_photo_id_" + photoIndex);
        var url = $.cookie("clarify_photo_url_" + photoIndex);
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
                var name = $.cookie("clarify_album_name_" + albumIndex);
                var number = $.cookie("clarify_photo_count");
                $(".current").html(name + " [" + (photoIndex + 1) + "/" + number + "]");
                if ("" !== html) {
                    savePhotoClarifyResult(photoIndex, html);
                }
                clarifyPhoto(pageURL, albumIndex, photoIndex + 1, callback);
            },
            error : function() {
                var name = $.cookie("clarify_album_name_" + albumIndex);
                var number = $.cookie("clarify_photo_count");
                $(".current").html(name + " [" + (photoIndex + 1) + "/" + number + "]");
                clarifyPhoto(pageURL, albumIndex, photoIndex + 1, callback);
            }
        });
    } else {
        callback(pageURL, albumIndex);
    }
}

/**
 * 对相册进行分类。
 * @param {string} pageURL 用户分类请求的网址。
 * @param {int} albumIndex 当前相册的索引。
 */
function clarifyAlbum(pageURL, albumIndex) {
    $(".current").attr("class", "history");
    if (albumIndex < $.cookie("clarify_album_count")) {
        var name = $.cookie("clarify_album_name_" + albumIndex);
        var id = $.cookie("clarify_album_id_" + albumIndex);
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
                    $.cookie("clarify_photo_id_" + count, json[index].PhotoID, {expires: 1, path : "/"});
                    $.cookie("clarify_photo_url_" + count, json[index].PhotoPath, {expires : 1, path : "/"});
                    ++ count;
                });
                $.cookie("clarify_photo_count", count, {expires : 1, path : "/"});
                $(".current").html(name + " [0/" + count + "]");
                clarifyPhoto(pageURL, albumIndex + 1, 0, clarifyAlbum);
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
 * @param {type} resultIndex 结果的索引。
 */
function saveClarifyResult(resultIndex) {
    $.ajax({
        url : "ajax_save_result.php",
        type : "GET", 
        data : {resultid : resultIndex},
        dataType : "html",
        timeout : 180000,
        async: false
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
        $.cookie("clarify_album_count", 0, {expires : 1, path : "/"});
        $.cookie("clarify_photo_count", 0, {expires : 1, path : "/"});
        restore();
    });
    
    /**
     * 保存分类结果。
     */
    $("#Button_Save").click(function() {
        $("input[name='Checkbox_Result']").each(function() {
            if ($(this).prop("checked")) {
                $(this).prop("checked", false);
                $(this).prop("disabled", true);
                saveClarifyResult($(this).val());
                $(this).parent().parent().fadeOut(500);
            }
        });
    });
});