<?php
/**
 * 获取商品分类的列表。
 * @author ZHG <CyberZHG@gmail.com>
 */
require_once "setting.php";

$parentID = "0";
if (isset($_GET["parent"])) {
    $parentID = $_GET["parent"];
}
$fileName = DATA_PATH . "category/Category_" . $parentID;
$file = fopen($fileName, "r");
if ($file) {
    $category = "";
    while (!feof($file)) {
        $category .= fread($file, 1024);
    }
    echo $category;
}
?>
