<?php
/*
 * 将数据库中的特征保存为文本。
 * @author ZHG <CyberZHG@gmail.com>
 */

$sql = SQLQuery::getInstance();
$query = "SELECT * FROM D_Item_Feature;";
$sql->query($query);
$result = $sql->getResult();
$total = count($result);
$current = 0;
foreach ($result as $item) {
    ++ $current;
    echo $current . "/" . $total . "\n";
    $types = $item["Type"];
    $type = "feature_";
    for ($i = 0; $i < strlen($types); ++$i) {
        if ($types[$i] === ".") {
            break;
        }
        $type += $types[$i];
    }
    $filePath = IMAGE_FEATURE_PATH . $type . ".feature";
    $file = fopen($filePath, "a");
    if ($file) {
        fwrite($file, $item["ItemID"] . "\n");
        fwrite($file, $item["Price"] . "\n");
        fwrite($file, $type . "\n");
        fwrite($file, $item["ShapeFeature"] . "\n");
        fwrite($file, $item["ColorFeature"] . "\n");
        fwrite($file, $item["TextureFeature"] . "\n");
        fclose($file);
    }
}
?>
