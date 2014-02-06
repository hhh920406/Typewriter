<?php
/**
 * 检测表D_Seller是否存在，如果不存在就创建。
 * @author ZHG <CyberZHG@gmail.com>
 */
echo "<h2>Table: D_Seller</h2>";
$query = getTableExistanceString("D_Seller");
echo $query . "<br/>";
$sql->query($query);
if ($sql->getError()) {
    echo "查询出错：" . $sql->getError() . "<br/>";
} else {
    $result = $sql->getResult();
    if (count($result)) {
        echo "D_Seller表已经存在，不需要创建。<br/>";
    } else {
        $query =    "CREATE TABLE D_Seller (" . 
                        "ID INT(4) NOT NULL AUTO_INCREMENT, " . 
                        "PRIMARY KEY (ID), " .
                        "RemoteID INT(4), " . 
                        "Name VARCHAR(50), " . 
                        "Url TEXT, " . 
                        "Logo TEXT, " . 
                        "Source VARCHAR(50)" . 
                    ");";
        echo $query . "<br/>";
        $sql->query($query);
        if ($sql->getError()) {
            echo "创建表D_Seller失败：" . $sql->getError() . "<br/>";
        } else {
            echo "创建表D_Seller完成<br/>";
        }
    }
}
echo "<hr/>";
?>
