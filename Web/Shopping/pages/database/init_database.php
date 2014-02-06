<?php
/**
 * 检测Schema是否存在，如果不存在就创建。
 * @author ZHG <CyberZHG@gmail.com>
 */
echo "<h2>Database: " . SQL_DATABASE . "</h2>";
$query = "SELECT * FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMA_NAME = '" . SQL_DATABASE . "';";
echo $query . "<br/>";
$sql->query($query);
$result = $sql->getResult();
if (count($result)) {
    echo "数据库已经存在。<br/>";
} else {
    $query = "CREATE DATABASE '" . SQL_DATABASE . "';";
    echo $query . "<br/>";
    $sql->query("CREATE DATABASE " . SQL_DATABASE . " DEFAULT CHARACTER SET utf8 COLLATE utf8_unicode_ci;");  
    if ($sql->getError()) {
        echo "创建数据库出错：" . $sql->getError() . "<br/>";
        echo "过程停止。<br/>";
        return;
    } else {
        echo "创建数据库" . SQL_DATABASE . "完成。<br/>";
        $sql->initConnection();
    }
}
echo "<hr/>";
?>
