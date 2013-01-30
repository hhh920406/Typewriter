<?php
/**
 * The ajax page for judging if the album name is already exist.
 * @author ZHG <CyberZHG@gmail.com>
 */
include_once "sdk/apiRequestService.php";
$api = new ApiRequestService();
$albumName = $_GET["albumname"];
$result = $api->selectAlbumByName($albumName);
if(count($result) > 0) {
    echo "相册已经存在";
}
?>
