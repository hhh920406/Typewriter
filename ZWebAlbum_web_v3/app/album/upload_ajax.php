<?php
include_once "sdk/apiRequestService.php";
$albumID = $_GET["albumid"];
$photoPath = $_GET["photopath"];
$api = new ApiRequestService();
echo $api->insertPhoto($albumID, $photoPath);
?>
