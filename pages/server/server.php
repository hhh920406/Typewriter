<?php
/**
 * 通信的基本接口。
 * 本文件禁止被其他文件引用。
 * @author ZHG <CyberZHG@gmail.com>
 */
 require_once "../util/setting.php";
if (isset($_POST["method"])) {
    $fileName = FILE_ROOT . "pages/server/server." . $_POST["method"] . ".php";
    if (file_exists($fileName)) {
        require_once $fileName;
    } else {
        return json_encode(array("error" => "请求的方法不存在。"));
    }
} else {
    return json_encode(array("error" => "没有定义请求的方法。"));
}
?>
