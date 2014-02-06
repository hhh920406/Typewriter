<?php
if(isset($_POST["method"]))
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
                echo json_encode(array("error" => "The method doesn't exist. "));
            }
        }
        else
        {
            echo json_encode(array("error" => "The token is not exist. "));
        }
    }
}
else
{
    echo json_encode(array("error" => "The method is not given. "));
}
?>
