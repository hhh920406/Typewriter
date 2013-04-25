<?php
/**
 * 进行商品搜索的主页。
 * @author ZHG <CyberZHG@gmail.com>
 */
require_once "../util/setting.php";
require_once "../util/smarty.php";
if (isset($_GET["token"])) {
    $smarty->assign("empty", false);
} else {
    $smarty->assign("empty", true);
}
$smarty->display("search/index2.tpl");
?>
