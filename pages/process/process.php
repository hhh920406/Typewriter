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
        case "fiftynine.category":
            require_once "fiftynine/obtain_category.php";
            break;
        case "fiftynine.seller":
            require_once "fiftynine/obtain_seller.php";
            break;
        case "fiftynine.item.amazon":
            require_once "fiftynine/obtain_item.php";
            break;
        case "download.image":
            require_once "obtain_image.php";
            break;
        case "exit":
            return;
        default:
            echo "No such method.\n";
    }
}
?>
