<?php
/**
 * 检测表D_Item_EHD_RGB_80是否存在，如果不存在就创建。
 * @author ZHG <CyberZHG@gmail.com>
 */
echo "<h2>Table: D_Item_EHD_RGB_80</h2>";
$query = getTableExistanceString("D_Item_EHD_RGB_80");
echo $query . "<br/>";
$sql->query($query);
if ($sql->getError()) {
    echo "查询出错：" . $sql->getError() . "<br/>";
} else {
    $result = $sql->getResult();
    if (count($result)) {
        echo "D_Item_EHD_RGB_80表已经存在，不需要创建。<br/>";
    } else {
        $query =    "CREATE TABLE D_Item_EHD_RGB_80 (" . 
                        "ItemID INT(4) UNIQUE NOT NULL, " . 
                        "PRIMARY KEY (ItemID), " .
                        "Price INT(4), " . 
                        "Type TEXT, " .
                        "Title TEXT, " . 
                        "Image TEXT, " .
                        "Feature TEXT" . 
                    ");";
        echo $query . "<br/>";
        $sql->query($query);
        if ($sql->getError()) {
            echo "创建表D_Item_EHD_RGB_80失败：" . $sql->getError() . "<br/>";
        } else {
            echo "创建表D_Item_EHD_RGB_80完成<br/>";
        }
    }
}
echo "<hr/>";
?>
