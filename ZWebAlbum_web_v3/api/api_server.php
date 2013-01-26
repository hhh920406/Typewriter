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
            switch($_POST["method"])
            {
                case "user.basic":
                    include_once "server/user.basic.php";
                    break;
            }
        }
    }
}
?>
