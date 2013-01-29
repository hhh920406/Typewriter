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
            include_once "server/" . $_POST["method"] . ".php";
        }
    }
}
?>
