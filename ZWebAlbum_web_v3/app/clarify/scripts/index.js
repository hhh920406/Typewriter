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

$(function() {
    /**
     * 全选。
     */
    $("#Select_All").click(function() {
        $("input:checkbox").prop("checked", true);
        check();
    });
    
    /**
     * 取消全选。
     */
    $("#Select_None").click(function() {
        $("input:checkbox").prop("checked", false);
        check();
    });
    
    /**
     * 反选。
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
        //TODO
    });
    
    /**
     * 对时间进行分类。
     */
    $("#Link_Time").click( function() {
        //TODO
    });
    
    /**
     * 对事件进行分类。
     */
    $("#Link_Event").click( function() {
        //TODO
    });
});