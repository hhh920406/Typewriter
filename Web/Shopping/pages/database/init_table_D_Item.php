<?php
/**
 * 检测表D_Item是否存在，如果不存在就创建。
 * @author ZHG <CyberZHG@gmail.com>
 */
echo "<h2>Table: D_Item</h2>";
$query = getTableExistanceString("D_Item");
echo $query . "<br/>";
$sql->query($query);
if ($sql->getError()) {
    echo "查询出错：" . $sql->getError() . "<br/>";
} else {
    $result = $sql->getResult();
    if (count($result)) {
        echo "D_Item表已经存在，不需要创建。<br/>";
    } else {
        $query =    "CREATE TABLE D_Item (" . 
                        "ID INT(4) NOT NULL AUTO_INCREMENT, " . 
                        "PRIMARY KEY (ID), " .
                        "RemoteID vARCHAR(20), " . 
                        "Name TEXT, " . 
                        "Price TEXT, " . 
                        "Url TEXT, " . 
                        "Image TEXT, " . 
                        "SellerID INT(4), " . 
                        "CategoryID VARCHAR(50), " . 
                        "Source VARCHAR(50)" . 
                    ");";
        echo $query . "<br/>";
        $sql->query($query);
        if ($sql->getError()) {
            echo "创建表D_Item失败：" . $sql->getError() . "<br/>";
        } else {
            echo "创建表D_Item完成<br/>";
        }
    }
}
echo "<hr/>";
?>
