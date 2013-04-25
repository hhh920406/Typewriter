<?php
/**
 * 获取商品的相关数据。
 * @author ZHG <CyberZHG@gmail.com>
 */
if (isset($_GET["id"])) {
    require_once "setting.php";
    require_once "../database/SQLQuery.class.php";
    $sql = SQLQuery::getInstance();
    $id = $_GET["id"];
    $query = "SELECT * FROM D_Item WHERE ID = '$id';";
    $sql->query($query);
    if (!$sql->getError()) {
        $item = $sql->getResult();
        if (count($item)) {
            $item = $item[0];
            $result = new stdClass();
            $result->name = $item["Name"];
            $result->price = $item["Price"];
            $result->url = $item["Url"];
            $result->image = $item["Image"];
            echo json_encode($result);
        }
    }
}
?>
