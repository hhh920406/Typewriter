<?php
/**
 * 用于返回相册中照片的数量。QueryString中需要包含albumid为相册的ID。
 * @author ZHG <CyberZHG@gmail.com>
 */
require_once "sdk/apiRequestService.php";
$api = new ApiRequestService();
if (isset($_GET["albumid"])) {
    echo json_encode($api->selectPhotos($_GET["albumid"]));
}
?>
