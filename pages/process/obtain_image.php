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

$file = fopen("file", "r");
if ($file) {
    while (!feof($file)) {
        $path = fgets($file);
        $name = "";
        for ($i = strlen($path) - 1; $i >= 0; --$i) {
            if ($path[$i] === "&") {
                $name = "";
            }
            if ($path[$i] === "=" || $path[$i] === "/") {
                break;
            }
            $name = $path[$i] . $name;
        }
        downloadImage($path, "image/" . $name);
    }
    fclose($file);
}

$sql = SQLQuery::getInstance();
$count = 0;
for ($i = 0; ; $i += 100) {
    $query = "SELECT * FROM D_Item LIMIT $i, 100";
    echo "$query\n";
    $sql->query($query);
    if ($sql->getError()) {
        echo "Error: " . $sql->getError() . "\n";
    } else {
        $result = $sql->getResult();
        if (count($result) === 0) {
            break;
        }
        foreach ($result as $item) {
            $url = $item["Image"];
            $targetPath = IMAGE_PATH . $item["Source"] . "/" . $item["SellerID"] . "/" . $item["CategoryID"];
            if (!is_dir($targetPath)) {
                mkdir($targetPath, 0777, true);
            }
            $targetPath .= "/" . $item["RemoteID"];
            if (!file_exists($targetPath)) {
                echo "Start Download: $url\n";
                echo "Target Path: $targetPath.temp\n";
                if (downloadImage($url, $targetPath . ".temp")) {
                    rename($targetPath . ".temp", $targetPath . ".jpg");
                }
                ++ $count;
                echo "Total Number: $count\n";
                echo Date("Y-m-d H:i:s") . "\n";
            }
        }
    }
}
echo "Download Complete\n";
?>
