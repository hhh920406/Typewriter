<?php
/**
 * 返回查询的结果。
 * @author ZHG <CyberZHG@gmail.com>
 */
/**
 * 以逗号分割字符串。
 * @param string $str 要分割的字符串。
 * @return string 分割后的结果。
 */
function strSplit($str) {
    $result = array();
    $len = strlen($str);
    $temp = "";
    for ($i = 0; $i < $len; ++$i) {
        if ($str[$i] == ",") {
            $result[] = $temp;
            $temp = "";
        } else {
            $temp .= $str[$i];
        }
    }
    if ($temp) {
        $result[] = $temp;
    }
    return $result;
}

require_once "setting.php";
require_once "../database/SQLQuery.class.php";
if (isset($_GET["token"]) && isset($_GET["index"]) && isset($_GET["number"])) {
    $cachePath = TEMP_PATH . $_GET["token"] . ".cache";
    if (!file_exists($cachePath)) {
        $originImagePath = TEMP_PATH . $_GET["token"];
        $originFeature = exec(FILE_ROOT . "exec/EHD_RGB_80.exe " . $originImagePath);
        if ($originFeature != "-1") {
            $originFeature = strSplit($originFeature);
            $sql = SQLQuery::getInstance();
            $query = "SELECT * FROM D_Item_EHD_RGB_80;";
            $sql->query($query);
            $result = $sql->getResult();
            $ids = array();
            $dists = array();
            foreach ($result as $item) {
                $feature = $item["Property"];
                $feature = strSplit($feature);
                $dist = 0;
                for ($i = 0; $i < count($feature); ++$i) {
                    $dist += ($originFeature[$i] - $feature[$i]) * ($originFeature[$i] - $feature[$i]);
                }
                $ids[] = $item["ItemID"];
                $dists[] = $dist;
            }
            array_multisort($dists, SORT_ASC, SORT_NUMERIC, $ids);
            $file = fopen($cachePath, "w");
            if ($file) {
                fwrite($file, json_encode($ids));
                fclose($file);
            }
        }
    }
    $result = array();
    $file = fopen($cachePath, "r");
    if ($file) {
        $ids = "";
        while (!feof($file)) {
            $ids .= fread($file, 1024);
        }
        $ids = json_decode($ids);
        fclose($file);
        $index = $_GET["index"];
        $number = $_GET["number"];
        for ($i = 0; $i < $number; ++ $i) {
            if ($i + $index >= count($ids)) {
                break;
            }
            $result[] = $ids[$i + $index];
        }
    }
    echo json_encode($result);
    return;
}
echo json_encode(array());
?>
