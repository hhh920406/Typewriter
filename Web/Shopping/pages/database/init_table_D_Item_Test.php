<?php
/**
 * 检测表D_Item_Test是否存在，如果不存在就创建。
 * @author ZHG <CyberZHG@gmail.com>
 */
echo "<h2>Table: D_Item_Test</h2>";
$query = getTableExistanceString("D_Item_Test");
echo $query . "<br/>";
$sql->query($query);
if ($sql->getError()) {
    echo "查询出错：" . $sql->getError() . "<br/>";
} else {
    $result = $sql->getResult();
    if (count($result)) {
        echo "D_Item_Test表已经存在，不需要创建。<br/>";
    } else {
        $query =    "CREATE TABLE D_Item_Test (" . 
                        "ItemID INT(4) UNIQUE NOT NULL, " . 
                        "PRIMARY KEY (ItemID), " .
                        "Property TEXT" . 
                    ");";
        echo $query . "<br/>";
        $sql->query($query);
        if ($sql->getError()) {
            echo "创建表D_Item_Test失败：" . $sql->getError() . "<br/>";
        } else {
            echo "创建表D_Item_Test完成<br/>";
        }
    }
}
echo "<hr/>";
?>
