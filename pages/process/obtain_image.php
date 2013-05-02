<?php
/**
 * 从数据库的链接中下载图片。
 * @author ZHG <CyberZHG@gmail.com>
 */
function createDir($dir) {
    if (!file_exists($dir)) {
        createDir(dirname($dir));
        mkdir($dir, 0777);
    }
}

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

$count = 0;
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
        for ($i = 0; $i < count($ids); ++$i) {
            $infoFilePath = DATA_PATH . "info/item_" . $ids[$i];
            $item = "";
            if (file_exists($infoFilePath)) {
                $file = fopen($infoFilePath, "r");
                if ($file) {
                    while (!feof($file)) {
                        $item .= fread($file, 1024);
                    }
                    fclose($file);
                } else {
                    continue;
                }
                $item = json_decode($item);
            } else {
                continue;
            }
            $imageFilePath = DATA_PATH . "image/" . $ids[$i] . ".jpg";
            if (!file_exists($imageFilePath)) {
                if (downloadImage($item->image, $imageFilePath)) {
                    ++ $count;
                    echo "{$count}: $imageFilePath\n";
                }
            }
        }
    }
}
echo "Download Complete\n";
?>
