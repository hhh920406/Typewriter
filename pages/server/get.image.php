<?php
/**
 * 获取商品的相关数据。
 * @author ZHG <CyberZHG@gmail.com>
 */
if (isset($_GET["id"])) {
    require_once "setting.php";
    $id = $_GET["id"];
    $fileName = DATA_PATH . "info/item_" . $id;
    if (file_exists($fileName)) {
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
