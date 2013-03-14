<?php
/**
 * 返回查询的结果。
 * @author ZHG <CyberZHG@gmail.com>
 */
/**
 * 以逗号或空格分割字符串。
 * @param string $str 要分割的字符串。
 * @return string 分割后的结果。
 */
function strSplit($str) {
    $result = array();
    $len = strlen($str);
    $temp = "";
    for ($i = 0; $i < $len; ++$i) {
        if ($str[$i] == "," || $str[$i] == " ") {
            if ($temp) {
                $result[] = $temp;
                $temp = "";
            }
        } else {
            $temp .= $str[$i];
        }
    }
    if ($temp) {
        $result[] = $temp;
    }
    return $result;
}

/**
 * 获取搜索的条件。
 * @return stdClass 搜索条件。
 */
function getCondition() {
    $condition = new stdClass();
    if (isset($_GET["start_price"]) && isset($_GET["end_price"])) {
        $condition->startPrice = $_GET["start_price"];
        $condition->endPrice = $_GET["end_price"];
    }
    if (isset($_GET["keyword"])) {
        $condition->keyword = strSplit(urldecode($_GET["keyword"]));
    }
    if (isset($_GET["type"])) {
        $condition->type = urldecode($_GET["type"]);
    }
    return $condition;
}

/**
 * 获取缓存文件的名称。
 * @param stdClass 当前的条件。
 * @return type
 */
function getCacheName($condition) {
    $name = json_encode($condition);
    if (isset($_GET["token"])) {
        $name .= $_GET["token"];
    }
    return md5($name) . ".cache";
}

require_once "setting.php";
require_once "../database/SQLQuery.class.php";
if (isset($_GET["token"]) && isset($_GET["index"]) && isset($_GET["number"])) {
    $condition = getCondition();
    $cacheName = getCacheName($condition);
    $cachePath = TEMP_PATH . $cacheName;
    if (!file_exists($cachePath)) {
        $originImagePath = TEMP_PATH . $_GET["token"];
        $originFeature = exec(FILE_ROOT . "exec/EHD_RGB_80.exe " . $originImagePath);
        if ($originFeature !== "-1") {
            $originFeature = strSplit($originFeature);
            $sql = SQLQuery::getInstance();
            if (isset($condition->startPrice) && isset($condition->endPrice)) {
                $startPrice = $condition->startPrice;
                $endPrice = $condition->endPrice;
                $query = "SELECT * FROM D_Item_EHD_RGB_80 WHERE Price >= '$startPrice' AND Price < '$endPrice';";
            } else {
                $query = "SELECT * FROM D_Item_EHD_RGB_80;";
            }
            $sql->query($query);
            $result = $sql->getResult();
            $ids = array();
            $dists = array();
            foreach ($result as $item) {
                $feature = $item["Feature"];
                if ($feature === "-1") {
                    continue;
                }
                $feature = strSplit($feature);
                if (count($feature) != count($originFeature)) {
                    continue;
                }
                $dist = 0;
                for ($i = 0; $i < count($feature); ++$i) {
                    $dist += ($originFeature[$i] - $feature[$i]) * ($originFeature[$i] - $feature[$i]);
                }
                if (isset($condition->keyword)) {
                    foreach ($condition->keyword as $word) {
                        if (strpos($item["Title"], $word) !== false) {
                            $dist -= 10000;
                        }
                    }
                }
                if (isset($condition->type)) {
                    if (strpos($item["Type"], $condition->type) === false) {
                        $dist += 100000;
                    }
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
