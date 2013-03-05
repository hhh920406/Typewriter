<?php
include_once "sdk/apiRequestService.php";
$api = new ApiRequestService();
if(isset($_GET["albumid"])) {
    $api->deleteAlbum($_GET["albumid"]);
}
?>
