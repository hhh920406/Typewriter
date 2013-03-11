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
        case "obtain_category":
            require_once "obtain_category.php";
            echo "Source: ";
            fscanf(STDIN, "%s", $method);
            obtainCategory($method);
            return;
        case "fiftynine.seller":
            require_once "fiftynine/obtain_seller.php";
            return;
        case "fiftynine.item.amazon":
            require_once "fiftynine/obtain_item.php";
            return;
        case "download.image":
            require_once "obtain_image.php";
            return;
        case "exit":
            return;
        default:
            echo "No such method.\n";
    }
}
?>
