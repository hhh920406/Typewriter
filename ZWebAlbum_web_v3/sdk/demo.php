<?php
include_once "apiRequestService.php";

$api = new ApiRequestService();
echo $api->getUserToken();
?>
