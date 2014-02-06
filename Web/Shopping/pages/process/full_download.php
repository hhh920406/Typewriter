<?php

function createDir($dir) {
    if (!file_exists($dir)) {
        createDir(dirname($dir));
        mkdir($dir, 0777);
    }
}

function downloadImage($url, $targetPath) {
    createDir(dirname($targetPath));
    $ch = curl_init($url);
    $targetFile = fopen($targetPath . ".temp", "wb");
    curl_setopt($ch, CURLOPT_FILE, $targetFile);
    curl_setopt($ch, CURLOPT_HEADER, 0);
    curl_setopt($ch, CURLOPT_TIMEOUT, 16);
    curl_setopt($ch, CURLOPT_FOLLOWLOCATION, 1);
    curl_exec($ch);
    $error = curl_error($ch);
    curl_close($ch);
    fclose($targetFile);
    rename($targetPath . ".temp", $targetPath);
    return $error === "";
}

function full_download($sellerID, $categoryID, $keyword, $pageNum, $itemPerPage = "20") {
    $sourceName = DataSourceManager::RESOURCE_FIFTYNINE;
    $source = new DataSourceManager($sourceName);
    $items = $source->getItemList($sellerID, $categoryID, $keyword, "0", "9999999", $pageNum, $itemPerPage);
    foreach ($items as $item) {
        $infoPath = DATA_PATH . "item/item_" . $item->itemID;
        if (!file_exists($infoPath)) {
            $itemInfo = new stdClass();
            $itemInfo->name = $item->itemName;
            $itemInfo->price = $item->itemPrice;
            $itemInfo->url = $item->itemUrl;
            $itemInfo->image = $item->itemImage;
            $file = fopen($infoPath, "w");
            if ($file) {
                fwrite($file, json_encode($itemInfo));
                fclose($file);
            }
            echo "Create info: {$infoPath}\n";
            $file = fopen("item.list", "a");
            if ($file) {
                fwrite($file, "{$item->itemID} {$item->categoryID} {$item->sellerID} {$item->itemPrice}\n");
                fclose($file);
            }
        }
        $imagePath = DATA_PATH . "image/" . $item->itemID . ".jpg";
        if (!file_exists($imagePath)) {
            if (downloadImage($item->itemImage, $imagePath)) {
                copy($imagePath, "ti/" . $item->itemID . ".jpg");
                echo "Download image: {$imagePath}\n";
            }
        }
    }
}

for ($i = 1; $i <= 99; ++$i) {
    echo "Page {$i}\n";
    //full_download("", "", "格子围巾", $i);
    //full_download("", "", "格子", $i);
    //full_download("", "", "围巾", $i);
    //full_download("", "", "burberry", $i);
    full_download("", "", "burberry 围巾", $i);
}
?>
