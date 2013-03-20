<?php
/**
 * 提取图像的特征。
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

$sql = SQLQuery::getInstance();
//$query = "DELETE FROM D_Item_Feature;";
//$sql->query($query);
$query = "SELECT * FROM D_Category WHERE Source = 'fiftynine';";
$sql->query($query);
$category = $sql->getResult();
$parent = array();
foreach ($category as $item) {
    $parent[$item["RemoteID"]] = $item["Parent"];
}
$query = "SELECT COUNT(*) FROM D_Item WHERE Source = 'fiftynine';";
echo "$query\n";
$sql->query($query);
$num = $sql->getResult()[0][0];
echo "Total Number: $num\n";
for ($i = 0; $i < $num; $i += 50) {
    $query = "SELECT * FROM D_Item LIMIT $i, 50;";
    echo "$query\n";
    $sql->query($query);
    $result = $sql->getResult();
    foreach ($result as $item) {
        $targetPath = IMAGE_PATH . $item["Source"] . "/" . $item["SellerID"] . "/" . $item["CategoryID"] . "/" . $item["RemoteID"] . ".jpg";
        if (file_exists($targetPath)) {
            $id = $item["ID"];
            $query = "SELECT COUNT(*) FROM D_Item_Feature WHERE ItemID = '$id';";
            $sql->query($query);
            $count = $sql->getResult()[0][0];
            if ($count == 0) {
                $types = strSplit($item["CategoryID"]);
                for ($j = 0; $j < count($types); ++ $j) {
                    if ($parent[$types[$j]] == 0) {
                        $types = $types[$j];
                        break;
                    } else if($parent[$parent[$types[$j]]] == 0) {
                        $types = $parent[$types[$j]];
                        break;
                    }
                }
                if (is_array($types)) {
                    continue;
                }
                $shapeFeature = exec(FILE_ROOT . "exec/EHD_RGB_80.exe " . $targetPath);
                $colorFeature = exec(FILE_ROOT . "exec/72HSV.exe ". $targetPath);
                $textureFeature = "";
                $query = "INSERT INTO D_Item_Feature " . 
                         "(ItemID, Price, Type, Title, Image, ShapeFeature, ColorFeature, TextureFeature) VALUES " . 
                         "('" . $id . 
                         "', '" . $item["Price"] . 
                         "', '" . $types . 
                         "', '" . $item["Name"] . 
                         "', '" . $item["Image"] . 
                         "', '" . $shapeFeature . 
                         "', '" . $colorFeature . 
                         "', '" . $textureFeature . "');";
                echo "$query\n";
                $sql->query($query);
                if ($sql->getError()) {
                    echo "Insert Error: " . $sql->getError() . "\n";
                }
            }
        }
    }
}
?>
