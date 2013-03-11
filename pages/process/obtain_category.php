<?php
/**
 * 获取分类信息到数据库中。
 * @author ZHG <CyberZHG@gmail.com>
 */

/**
 * 获取分类数据。
 * @param string $sourceName 数据来源的名称。
 */
function obtainCategory($sourceName) {
    $source = new DataSourceManager($sourceName);
    $sql = SQLQuery::getInstance();
    $query = "DELETE FROM D_Category WHERE Source = '" . $sourceName . "';";
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
            if (++ $errorCount > 1) {
                break;
            }
            $result = $source->getCategoryList($parentID);
            echo "Failed " . $errorCount . " time(s). \n";
            sleep(3);
        }
        if ($errorCount <= 1) {
            foreach ($result as $item) {
                $query = "INSERT INTO D_Category " . 
                         "(RemoteID, Name, Parent, IsParent, Source) " .
                         "VALUES " .
                         "('" . $item->categoryID . "', '" . $item->categoryName . 
                         "', '" . $item->parentID . "', '" . (int)$item->isParent . 
                         "', '" . $sourceName . "');";
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
}
?>
