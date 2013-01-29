<?php
if(isset($_POST["API_KEY"]) && isset($_POST["method"]))
{
    if($_POST["method"] == "token")
    {
        include_once "server/token.php";
    }
    else
    {
        if(isset($_POST["token"]))
        {
            $token = $_POST["token"];
            $filename = "server/" . $_POST["method"] . ".php";
            if(file_exists($filename))
            {
                include_once $filename;
            }
            else
            {
                echo json_encode(array("error", "请求操作不存在。"));
            }
        }
        else
        {
            echo json_encode(array("error", "没有给出用户令牌。"));
        }
    }
}
else
{
    echo json_encode(array("error", "没有提供API Key或操作方法。"));
}
?>
