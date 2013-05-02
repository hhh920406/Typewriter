<?php
/**
 * 通过文本中的数据定向更新数据库的内容。
 * @author ZHG <CyberZHG@gmail.com>
 */
$source = new DataSourceManager("fiftynine");
$filePath = "D:/Apache2.2/htdocs/ZShopping_web/exec/Item.list";
$savePath = "D:/Apache2.2/htdocs/ZShopping_web/exec/Item.save";
$dataFile = fopen($filePath, "r");
if ($dataFile) {
    $data = "";
    while (!feof($dataFile)) {
        $data .= fread($dataFile, 1024);
    }
    fclose($dataFile);
    $saveFile = fopen($savePath, "r");
    if ($saveFile) {
        $startIndex = fread($saveFile, 1024);
        fclose($saveFile);
        if ($startIndex === "") {
            $startIndex = 0;
        }
        $lines = array();
        $temp = "";
        $data = preg_replace('/\n|\r\n/', '_', $data);
        $len = strlen($data);
        for ($i = 0; $i < $len; ++$i) {
            if ($data[$i] == "_") {
                $lines[] = $temp;
                $temp = "";
            } else {
                $temp .= $data[$i];
            }
        }
        $ids = array();
        for ($i = 0; $i < count($lines); ++$i) {
            $temp = "";
            for ($j = 0; $j < strlen($lines[$i]); ++$j) {
                if ($lines[$i][$j] === " ") {
                    break;
                }
                $temp .= $lines[$i][$j];
            }
            $ids[] = $temp;
        }
        for ($i = $startIndex; $i < count($ids);) {
            $iids = "";
            for ($j = 0; $i + $j < count($ids) && $j < 10; ++$j) {
                if ($j) {
                    $iids .= ",";
                }
                $iids .= $ids[$i + $j];
            }
            $items = $source->getItem($iids);
            for ($j = 0; $j < count($items); ++$j) {
                $result = new stdClass();
                $result->name = $items[$j]->itemName;
                $result->price = $items[$j]->itemPrice;
                $result->url = $items[$j]->itemUrl;
                $result->image = $items[$j]->itemImage;
                $result = json_encode($result);
                $file = fopen("D:/Apache2.2/htdocs/ZShopping_web/temp/search/item_" . $items[$j]->itemID, "w");
                if ($file) {
                    echo "D:/Apache2.2/htdocs/ZShopping_web/temp/search/item_" . $items[$j]->itemID . "\n";
                    fwrite($file, $result);
                    fclose($file);
                }
            }
            $i += 10;
            echo "{$i}\n";
            $saveFile = fopen($savePath, "w");
            if ($saveFile) {
                fwrite($saveFile, $i);
                fclose($saveFile);
            }
        }
    }
}
?>
