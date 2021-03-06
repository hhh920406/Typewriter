<?php
/**
 * 从数据库的链接中下载图片。
 * @author ZHG <CyberZHG@gmail.com>
 */
/**
 * 下载图片到指定位置
 * @param string $url 原位置。
 * @param string $targetPath 目的地址。
 * @return boolean 如果成功返回true，否则返回false。
 */
function downloadImage($url, $targetPath) {
    $originFile = fopen($url, "rb");
    if ($originFile) {
        $targetFile = fopen($targetPath, "wb");
        if ($targetFile) {
            while (!feof($originFile)) {
                fwrite($targetFile, fread($originFile, 1024 * 4), 1024 * 4);
            }
            fclose($targetFile);
            fclose($originFile);
            return true;
        }
    }
    return false;
}

$sql = SQLQuery::getInstance();
$count = 0;
$query = "SELECT COUNT(*) FROM D_Item";
$sql->query($query);
for ($i = $sql->getResult()[0][0] - 100; ; $i -= 100) {
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
