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
    $queue = array(0);
    $depth = array(0);
    $source = new DataSourceManager($sourceName);
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
            $jsonResult = array();
            foreach ($result as $item) {
                $jsonResult[] = array("id" => $item->categoryID, "name" => $item->categoryName);
                if ($item->isParent) {
                    if ($depth[$i] < 2) {
                        $queue[] = $item->categoryID;
                        $depth[] = $depth[$i] + 1;
                    }
                }
            }
            $jsonResult = json_encode($jsonResult);
            $file = fopen("Category_" . $parentID, "w");
            fwrite($file, $jsonResult);
            fclose($file);
        }
    }
}
?>
