<?php
include_once "sdk/apiRequestService.php";
$api = new ApiRequestService();
$api->getUserToken("Monkey012");
$basic = $api->getUserBasic();
$smarty->assign("basic", $basic);
?>
