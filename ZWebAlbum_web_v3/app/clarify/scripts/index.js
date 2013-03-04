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
        $("")
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
    $(".albumBlock").slideDown(1500);
    check();
    $(".processBlock").slideUp(500);
}

/**
 * 进入处理阶段。
 */
function showProcessBlock() {
    $(".albumBlock").slideUp(300,function() {
        $(".selectBlock").slideUp(300, function() {
            $(".processBlock").slideDown(500);
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
            $.cookie("clarify_album_name" + count, name, {expires : 1, path : "/"});
            $.cookie("clarify_album_id" + count, id, {expires : 1, path : "/"});
            ++ count;
        }
    });
    $.cookie("clarify_album_count", count, {expires: 1, path : "/"});
}

/**
 * 对图片进行分类。
 * @param {string} page 用户分类请求的网址。
 * @param {int} albumIndex 当前相册的索引。
 * @param {int} photoIndex 当前照片的索引。
 * @param {function} callback 回调函数。
 */
function clarifyPhoto(pageURL, albumIndex, photoIndex, callback) {
    if (photoIndex < $.cookie("clarify_photo_count")) {
        var id = $.cookie("clarify_photo_id" + photoIndex);
        var url = $.cookie("clarify_photo_url" + photoIndex);
        url = encodeURIComponent(url);
        $.ajax({
            url : pageURL,
            type : "GET", 
            data : {
                photoid : id,
                photourl : url
            },
            dataType : "json",
            timeout : 5000,
            success : function() {
                var name = $.cookie("clarify_album_name" + albumIndex);
                var number = $.cookie("clarify_photo_count");
                $(".current").html(name + " [" + (photoIndex + 1) + "/" + number + "]");
                clarifyPhoto(pageURL, albumIndex, photoIndex + 1, callback);
            },
            error : function() {
                var name = $.cookie("clarify_album_name" + albumIndex);
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
 * @param {string} page 用户分类请求的网址。
 * @param {int} albumIndex 当前相册的索引。
 */
function clarifyAlbum(pageURL, albumIndex) {
    $(".current").attr("class", "history");
    if (albumIndex < $.cookie("clarify_album_count")) {
        var name = $.cookie("clarify_album_name" + albumIndex);
        var id = $.cookie("clarify_album_id" + albumIndex);
        $("#UL_Process").append("<li class = 'current'></li>");
        $.ajax({
            url : "ajax_get_photos.php",
            type : "GET", 
            data : {albumid : id},
            dataType : "json",
            timeout : 5000,
            success : function(json) {
                var count = 0;
                $.each(json, function(index) {
                    $.cookie("clarify_photo_id" + count, json[index].PhotoID, {expires: 1, path : "/"});
                    $.cookie("clarify_photo_url" + count, json[index].PhotoPath, {expires : 1, path : "/"});
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
    }
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
    })
    
    /**
     * 对颜色进行分类。
     */
    $("#Link_Color").click( function() {
        showProcessBlock();
        recordSelection();
        clarifyAlbum("ajax_clarify_color.php", 0);
    });
    
    /**
     * 对时间进行分类。
     */
    $("#Link_Time").click( function() {
        showProcessBlock();
        recordSelection();
        clarifyAlbum("ajax_clarify_time.php", 0);
    });
    
    /**
     * 对事件进行分类。
     */
    $("#Link_Event").click( function() {
        showProcessBlock();
        recordSelection();
        clarifyAlbum("ajax_clarify_event.php", 0);
    });
});