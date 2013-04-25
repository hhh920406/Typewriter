<?php
/**
 * 通信的基本接口。
 * 本文件禁止被其他文件引用。
 * @author ZHG <CyberZHG@gmail.com>
 */
 require_once "../util/setting.php";
$method = "";
if (isset($_GET["method"])) {
    $method = $_GET["method"];
} else if (isset($_POST["method"])) {
    $method = $_POST["method"];
}
if ($method !== "") {
    $fileName = FILE_ROOT . "pages/server/" . $method . ".php";
    if (file_exists($fileName)) {
        require_once $fileName;
    } else {
        echo json_encode(array("错误" => "请求的方法不存在。"));
    }
} else {
    echo json_encode(array("错误" => "没有定义请求的方法。"));
}
?>
