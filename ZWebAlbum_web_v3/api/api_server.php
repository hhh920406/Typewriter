<?php
if(isset($_POST["method"]))
{
    switch($_POST["method"])
    {
        case "token":
            include_once "account/account_user.php";
            if(isset($_POST["name"]) && isset($_POST["password"]))
            {
                $name = $_POST["name"];
                $password = $_POST["password"];
                $result = Account_User::login($name, $password);
                if($result == LOGIN_SUCCESS)
                {
                    echo json_encode(array(
                        "token" => session_id()));
                }
                else
                {
                    echo json_encode(array(
                        "token" => "",
                        "error" => Account_User::getLoginMessage($result)));
                }
            }
            else
            {
                session_start();
                if(isset($_SESSION["User_ID"]))
                {
                    echo json_encode(array(
                        "token" => session_id()));
                }
                else
                {
                    echo json_encode(array(
                        "token" => "",
                        "error" => "没有用户登录"));
                }
            }
            break;
    }
}
?>
