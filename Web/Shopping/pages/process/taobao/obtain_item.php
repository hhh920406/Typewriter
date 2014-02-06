<?php
/**
 * 获取商品的数据到数据库中。
 * @author ZHG <CyberZHG@gmail.com>
 */
$sourceName = DataSourceManager::RESOURCE_TAOBAO;
$source = new DataSourceManager($sourceName);
$sql = SQLQuery::getInstance();
$query = "SELECT * FROM D_Category WHERE Source = '$sourceName';";
echo "$query\n";
$sql->query($query);
if ($sql->getError()) {
    echo "Select Error: " . $sql->getError() . "\n";
    return;
}
$categoryList = $sql->getResult();
$sellerID = 0;
$query = "SELECT COUNT(*) FROM D_Item WHERE Source = '$sourceName';";
$sql->query($query);
$count = $sql->getResult()[0][0];
echo "Old Count: $count \n";
$categoryCount = 0;
$startCategoryID = 50050359;
$startPageNumber = 5;
$lastResult = array();
$isStart = false;
foreach ($categoryList as $category) {
    ++ $categoryCount;
    $categoryID = $category["RemoteID"];
    echo "$categoryID\n";
    if (!$isStart && $categoryID != $startCategoryID) {
        continue;
    }
    $start = 1;
    if ($categoryID == $startCategoryID) {
        $isStart = true;
        $start = $startPageNumber;
    }
    for ($i = $start; $i <= 10; ++ $i) {
        $result = $source->getItemList($sellerID, $categoryID, "", 0, 0, $i, 40);
        if (count($result) === 0) {
            break;
        }
        foreach ($result as $item) {
            $query = "SELECT * FROM D_Item " . 
                     "WHERE Source = '" . $sourceName . "' " .
                     "AND RemoteID = '" . $item->itemID . "'; ";
            //echo $query . "\n";
            $sql->query($query);
            if ($sql->getError()) {
                echo "Select Error: " . $sql->getError() . "\n";
            } else {
                if (count($sql->getResult()) === 0) {
                    $query = "INSERT INTO D_Item " . 
                             "(RemoteID, Name, Price, Url, Image, SellerID, CategoryID, Source) " . 
                             "VALUES " .
                             "('" . $item->itemID . "', '" . $item->itemName . 
                             "', '" . $item->itemPrice . "', '" . $item->itemUrl . 
                             "', '" . $item->itemImage . "', '" . $item->sellerID . 
                             "', '" . $item->categoryID . "', '" . $sourceName . "');";
                    echo $query . "\n";
                    $sql->query($query);
                    if ($sql->getError()) {
                        echo "Insert Error: " . $sql->getError() . "\n";
                    } else {
                        ++ $count;
                    }
                } else {
                    /*$query = "UPDATE D_Item SET " . 
                             "Name = '" . $item->itemName . "', " .
                             "Price = '" . $item->itemPrice . "', " .
                             "Url = '" . $item->itemUrl . "' " .
                             "WHERE Source = '" . $sourceName . "' " .
                             "AND RemoteID = '" . $item->itemID . "'; ";
                    echo $query . "\n";
                    $sql->query($query);
                    if ($sql->getError()) {
                        echo "Update Error: " . $sql->getError() . "\n";
                    }*/
                }
            }
        }
        if (count($lastResult) === count($result)) {
            $same = true;
            for ($j = 0; $j < count($result); ++ $j) {
                if ($lastResult[$j]->itemID != $result[$j]->itemID) {
                    $same = false;
                    break;
                }
            }
            if ($same) {
                echo "Next Category\n";
                break;
            }
        }
        $lastResult = $result;
        echo "CategoryID: " . $categoryID . " " . $category["Name"] . "\n";
        echo "Page Number: " . $i . "\n";
        echo "Total Number: " . $categoryCount . " " . $count . "\n";
        echo Date("Y-m-d H:i:s") . "\n";
    }
}
?>
