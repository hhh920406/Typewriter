<?php
function downloadImage($url, $targetPath) {
    $originFile = fopen($url, "rb");
    if ($originFile) {
        $targetFile = fopen($targetPath, "wb");
        if ($targetFile) {
            while (!feof($originFile)) {
                fwrite($targetFile, fread($originFile, 1024 * 8), 1024 * 8);
            }
            fclose($targetFile);
            fclose($originFile);
            return true;
        }
    }
    return false;
}

if (isset($_GET["photoid"]) && isset($_GET["photourl"])) {
    set_time_limit(300);
    $url = urldecode($_GET["photourl"]);
    $type = "";
    for ($i = strlen($url) - 1; $i >= 0; -- $i) {
        $type = $url[$i] . $type;
        if ("." == $url[$i]) {
            break;
        }
    }
    $targetPath = $_SERVER["DOCUMENT_ROOT"] . "/app/clarify/exec/tempimage" . $type;
    downloadImage($url, $targetPath);
    $exePath = $_SERVER["DOCUMENT_ROOT"] . "/app/clarify/exec/Clarify_Color.exe";
    $command = $exePath . " " . $targetPath;
    $result = system($command);
    switch ($result) {
        case "0":
            $result = "红色";
            break;
        case "1":
            $result = "橙色";
            break;
        case "2":
            $result = "黄色";
            break;
        case "3":
            $result = "绿色";
            break;
        case "4":
            $result = "青色";
            break;
        case "5":
            $result = "蓝色";
            break;
        case "6":
            $result = "紫色";
            break;
    }
    echo json_encode($result);
}
?>
