<?php
/**
 * 通过文本中的数据定向更新数据库的内容。
 * @author ZHG <CyberZHG@gmail.com>
 */
function downloadImage($url, $targetPath) {
    createDir(dirname($targetPath));
    $originFile = fopen($url, "rb");
    if ($originFile) {
        $targetFile = fopen($targetPath . ".temp", "wb");
        if ($targetFile) {
            while (!feof($originFile)) {
                fwrite($targetFile, fread($originFile, 1024 * 4), 1024 * 4);
            }
            fclose($targetFile);
            fclose($originFile);
            rename($targetPath . ".temp", $targetPath);
            return true;
        }
    }
    return false;
}

$source = new DataSourceManager("fiftynine");
$filePath = "E:/zhg/scripts/item/item";
$savePath = "Item_Update.save";
$dataFile = opendir($filePath);
if ($dataFile) {
    $ids = array();
    while (($file = readdir($dataFile)) !== false) {
        $id = "";
        for ($i = 5; $i < strlen($file); ++$i) {
            $id .= $file[$i];
        }
        $ids[] = $id;
    }
    closedir($dataFile);
    $saveFile = fopen($savePath, "r");
    if ($saveFile) {
        $startIndex = fread($saveFile, 1024);
        fclose($saveFile);
        if ($startIndex === "") {
            $startIndex = 0;
        }
        /*$lines = array();
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
        }*/
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
                $overFile = fopen("item.list", "a");
                if ($overFile) {
                    fwrite($overFile, "{$items[$j]->itemID} {$items[$j]->categoryID} {$items[$j]->sellerID} {$items[$j]->itemPrice}\n");
                    fclose($overFile);
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
