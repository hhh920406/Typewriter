<?php
/**
 * 返回查询的结果。
 * @author ZHG <CyberZHG@gmail.com>
 */
require_once "setting.php";
/**
 * 获取搜索的条件。
 * @return stdClass 搜索条件。
 */
function getCondition() {
    $condition = new stdClass();
    if (isset($_GET["start_price"])) {
        $condition->startPrice = $_GET["start_price"];
    }
    if (isset($_GET["end_price"])) {
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
            $query = "SELECT * FROM D_Item_EHD_RGB_80";
            $flag = false;
            if (isset($condition->startPrice)) {
                $startPrice = $condition->startPrice;
                if ($flag) {
                    $query .= " AND ";
                } else {
                    $query .= " WHERE ";
                    $flag = true;
                }
                $query .= "Price >= '$startPrice'";
            }
            if (isset($condition->endPrice)) {
                $endPrice = $condition->endPrice;
                if ($flag) {
                    $query .= " AND ";
                } else {
                    $query .= " WHERE ";
                    $flag = true;
                }
                $query .= "Price <= '$endPrice'";
            }
            if (isset($condition->type)) {
                $type = $condition->type;
                if ($type !== "null") {
                    if ($flag) {
                        $query .= " AND ";
                    } else {
                        $query .= " WHERE ";
                        $flag = true;
                    }
                    $query .= "Type = '$type'";
                }
            }
            $query .= ";";
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
