<?php
include_once "sdk/apiRequestService.php";
$api = new ApiRequestService();
if(isset($_GET["photoid"])) {
    $api->deletePhoto($_GET["photoid"]);
}
?>
