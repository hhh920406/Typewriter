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
    $fileName = TEMP_PATH . "item_" . $id;
    if (!file_exists($fileName)) {
        $query = "SELECT * FROM D_Item WHERE RemoteID = '$id';";
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
                $result = json_encode($result);
                $file = fopen($fileName, "w");
                if ($file) {
                    fwrite($file, $result);
                    fclose($file);
                }
                echo $result;
            }
        }
    } else {
        $file = fopen($fileName, "r");
        if ($file) {
            $result = "";
            while (!feof($file)) {
                $result .= fread($file, 1024);
            }
            fclose($file);
            echo $result;
        }
    }
}
?>
