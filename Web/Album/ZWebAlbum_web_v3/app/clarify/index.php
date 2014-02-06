<?php
require_once "sdk/apiRequestService.php";
require_once "smarty_init.php";
$name = $_GET["username"];
$api = new ApiRequestService();
$api->getUserToken($name);
$albums = $api->selectAlbums();
$smarty->assign("albums", $albums);
$smarty->display("index.tpl");
?>
