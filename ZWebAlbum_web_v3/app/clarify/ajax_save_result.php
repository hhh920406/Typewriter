<?php
/**
 * 保存分类的结果，使用POST方式。传入值：
 * name：相册的名称。
 * list：照片ID的列表，用","或" "隔开。
 * @author ZHG <CyberZHG@gmail.com>
 */
if (isset($_POST["name"]) && isset($_POST["list"])) {
    require_once "sdk/apiRequestService.php";
    $api = new ApiRequestService();
    $name = $_POST["name"];
    $albumID = $api->insertAlbum($name, $name, 0);
    if ($albumID != 0) {
        $list = preg_split("/[/s+,]/", $_POST["list"]);
        for ($i = 0; $i < count($list); ++ $i) {
            $photoID = $api->insertPhotoById($albumID, $list[$i]);
            if ($photoID != 0) {
                $api->setAlbumCover($albumID, $photoID);
            }
        }
    }
}
?>
