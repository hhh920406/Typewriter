<?php
$basic = $_SESSION["basic"];
$smarty->assign("basic", $basic);
include_once "data.php";
$appid = $_GET["appid"];
$result = getApplicationByID($appid);
if(count($result) == 1) {
    $smarty->assign("appinfo", $result[0]);
} else {
    $smarty->assign("appinfo", "");
}
?>
