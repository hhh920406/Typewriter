<?php
/**
 * 获取商家的列表。
 * @author ZHG <CyberZHG@gmail.com>
 */
require_once "setting.php";

$fileName = DATA_PATH . "seller.list";
$file = fopen($fileName, "r");
if ($file) {
    $category = "";
    while (!feof($file)) {
        $category .= fread($file, 1024);
    }
    echo $category;
}
?>
