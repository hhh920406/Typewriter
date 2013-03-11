<?php
/**
 * 获取分类信息到数据库中。
 * @author ZHG <CyberZHG@gmail.com>
 */
$source = new DataSourceManager(DataSourceManager::RESOURCE_FIFTYNINE);
$sql = SQLQuery::getInstance();
$query = "DELETE FROM D_Category WHERE Source = '" . DataSourceManager::RESOURCE_FIFTYNINE . "';";
echo $query . "\n";
$sql->query($query);
if ($sql->getError()) {
    echo "Error: " . $sql->getError() . "\n";
    return;
} 
$queue = array(0);
for ($i = 0; $i < count($queue); ++ $i) {
    $parentID = $queue[$i];
    echo "Parent ID: " . $parentID . " Remaining: " . (count($queue) - $i - 1) . "\n";
    $result = $source->getCategoryList($parentID);
    $errorCount = 0;
    while (count($result) === 0) {
        if (++ $errorCount > 3) {
            break;
        }
        $result = $source->getCategoryList($parentID);
        echo "Failed " . $errorCount . " time(s). \n";
        sleep(10);
    }
    if ($errorCount <= 3) {
        foreach ($result as $item) {
            $query = "INSERT INTO D_Category " . 
                     "(RemoteID, Name, Parent, IsParent, Source) " .
                     "VALUES " .
                     "('" . $item->categoryID . "', '" . $item->categoryName . 
                     "', '" . $item->parentID . "', '" . (int)$item->isParent . 
                     "', '" . DataSourceManager::RESOURCE_FIFTYNINE . "');";
            echo $query . "\n";
            $sql->query($query);
            if ($sql->getError()) {
                echo "Error: " . $sql->getError() . "\n";
            }
            if ($item->isParent) {
                $queue[] = $item->categoryID;
            }
        }
    }
}
?>
