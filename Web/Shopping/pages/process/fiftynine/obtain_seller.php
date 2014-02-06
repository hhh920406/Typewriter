<?php
/**
 * 获取卖家信息到数据库中。
 * @author ZHG <CyberZHG@gmail.com>
 */
$sourceName = DataSourceManager::RESOURCE_FIFTYNINE;
$source = new DataSourceManager($sourceName);
$sql = SQLQuery::getInstance();
$query = "DELETE FROM D_Seller WHERE Source = '" . $sourceName . "';";
echo $query . "\n";
$sql->query($query);
if ($sql->getError()) {
    echo "Delete Error: " . $sql->getError() . "\n";
    return;
}
$count = 0;
for ($i = 1; $i < 99; ++ $i) {
    $result = $source->getSellerList($i, 40);
    if (count($result) === 0) {
        break;
    }
    echo "Page: " . $i . "\n";
    foreach ($result as $item) {
        $query = "INSERT INTO D_Seller " . 
                 "(RemoteID, Name, Url, Logo, Source) " . 
                 "VALUES " .
                 "('" . $item->sellerID . "', '" . $item->sellerName . 
                 "', '" . $item->sellerUrl . "', '" . $item->sellerLogo . 
                 "', '" . $sourceName . "');";
        echo $query . "\n";
        $sql->query($query);
        if ($sql->getError()) {
            echo "Insert Error: " . $sql->getError() . "\n";
        } else {
            ++ $count;
        }
    }
    sleep(10);
}
echo "Total Number: " . $count . "\n";
?>
