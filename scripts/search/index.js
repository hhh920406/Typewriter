/**
 * 主页的脚本。
 * @author ZHG <CyberZHG@gmail.com>
 */

/**
 * 进行搜索。
 */
function search() {
    //TODO
}

$(function() {
    // 详细配置的显示和隐藏。
    $("#Link_Config").click(function() {
        $(".searchConfigDetailDiv").fadeToggle(300);
    });
    // 在输入框按下回车时触发搜索。
    $(".searchText").keydown(function(event) {
        if (13 === event.keyCode) {
            search();
        }
    });
    // 点击搜索按钮后触发搜索。
    $(".searchButton").click(function() {
        search();
    });
});