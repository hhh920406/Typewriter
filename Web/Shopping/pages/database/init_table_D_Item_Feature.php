<?php
/**
 * 检测表D_Item_Feature是否存在，如果不存在就创建。
 * @author ZHG <CyberZHG@gmail.com>
 */
echo "<h2>Table: D_Item_Feature</h2>";
$query = getTableExistanceString("D_Item_Feature");
echo $query . "<br/>";
$sql->query($query);
if ($sql->getError()) {
    echo "查询出错：" . $sql->getError() . "<br/>";
} else {
    $result = $sql->getResult();
    if (count($result)) {
        echo "D_Item_EHD_RGB_80表已经存在，不需要创建。<br/>";
    } else {
        $query =    "CREATE TABLE D_Item_Feature (" . 
                        "ItemID INT(4) UNIQUE NOT NULL, " . 
                        "PRIMARY KEY (ItemID), " .
                        "Price INT(4), " . 
                        "Type INT(4), " .
                        "Title TEXT, " . 
                        "Image TEXT, " .
                        "ShapeFeature TEXT, " . 
                        "ColorFeature TEXT, " .
                        "TextureFeature TEXT" .
                    ");";
        echo $query . "<br/>";
        $sql->query($query);
        if ($sql->getError()) {
            echo "创建表D_Item_Feature失败：" . $sql->getError() . "<br/>";
        } else {
            echo "创建表D_Item_Feature完成<br/>";
        }
    }
}
echo "<hr/>";
?>
