<?php
/**
 * 获取商品分类的列表。
 * @author ZHG <CyberZHG@gmail.com>
 */
require_once "setting.php";
require_once "../database/SQLQuery.class.php";
$cacheName = TEMP_PATH . "category.cache";
if (!file_exists($cacheName)) {
    $sql = SQLQuery::getInstance();
    $query = "SELECT * FROM D_Category WHERE Parent = 0;";
    $sql->query($query);
    $result = $sql->getResult();
    $store = array();
    foreach ($result as $item) {
        $store[] = array("id" => $item["RemoteID"], "name" => $item["Name"]);
    }
    $file = fopen($cacheName, "w");
    if ($file) {
        fwrite($file, json_encode($store));
        fclose($file);
    }
}
$file = fopen($cacheName, "r");
if ($file) {
    $category = "";
    while (!feof($file)) {
        $category .= fread($file, 1024);
    }
    echo $category;
}
?>
