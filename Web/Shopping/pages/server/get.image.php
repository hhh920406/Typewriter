<?php
/**
 * 获取商品的相关数据。
 * @author ZHG <CyberZHG@gmail.com>
 */
if (isset($_GET["id"])) {
    require_once "setting.php";
    $id = $_GET["id"];
    $fileName = DATA_PATH . "item/item_" . $id;
    if (file_exists($fileName)) {
        $file = fopen($fileName, "r");
        if ($file) {
            $result = "";
            while (!feof($file)) {
                $result .= fread($file, 1024);
            }
            fclose($file);
            $result = json_decode($result);
            $result->image = DATA_URL . "image/" . $id . ".jpg";
            $result = json_encode($result);
            echo $result;
        }
    }
}
?>
