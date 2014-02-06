<?php
/**
 * 对数据库数据的获取和处理。
 * @author ZHG <CyberZHG@gmail.com>
 */
require_once "setting.php";
$method = "";
echo "ECHO\n";
while(fscanf(STDIN, "%s", $method) === 1) {
    switch ($method) {
        case "full":
            require_once "full_download.php";
            return;
        case "update":
            require_once "update_database.php";
            return;
        case "obtain_category":
            require_once "obtain_category.php";
            obtainCategory("fiftynine");
            return;
        case "fiftynine.seller":
            require_once "fiftynine/obtain_seller.php";
            return;
        case "fiftynine.item.amazon":
            require_once "fiftynine/obtain_item.php";
            return;
        case "fiftynine.item.taobao":
            require_once "taobao/obtain_item.php";
            return;
        case "download_image":
            require_once "obtain_image.php";
            return;
        case "download_image_reverse":
            require_once "obtain_image_reverse.php";
            return;
        case "feature":
            require_once "obtain_feature.php";
            return;
        case "transform_feature":
            require_once "transform_feature.php";
            return;
        case "exit":
            return;
        default:
            echo "No such method.\n";
    }
}
?>
