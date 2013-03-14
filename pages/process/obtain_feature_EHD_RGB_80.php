<?php
/**
 * 提取图像的EHD_RGB_80的特征。
 * @author ZHG <CyberZHG@gmail.com>
 */

$sql = SQLQuery::getInstance();
$query = "SELECT COUNT(*) FROM D_Item;";
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
            $query = "SELECT COUNT(*) FROM D_Item_EHD_RGB_80 WHERE ItemID = '$id';";
            $sql->query($query);
            $count = $sql->getResult()[0][0];
            if ($count == 0) {
                $feature = exec(FILE_ROOT . "exec/EHD_RGB_80.exe " . $targetPath);
                $query = "SELECT * FROM D_Category WHERE Source = '" . $item["Source"] . "' AND RemoteID = '" . $item["CategoryID"] . "';";
                echo "$query\n";
                $sql->query($query);
                if ($sql->getError()) {
                    echo "Select Error: " . $sql->getError() . "\n";
                }
                $type = $sql->getResult()[0]["Name"];
                $query = "INSERT INTO D_Item_EHD_RGB_80 " . 
                         "(ItemID, Price, Type, Title, Image, Feature) VALUES " . 
                         "('" . $id . 
                         "', '" . $item["Price"] . 
                         "', '" . $type . 
                         "', '" . $item["Name"] . 
                         "', '" . $item["Image"] . 
                         "', '" . $feature . "');";
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
