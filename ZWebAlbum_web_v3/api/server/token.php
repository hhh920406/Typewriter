<?php
if(isset($_POST["name"]))
{
    include_once $_SERVER['DOCUMENT_ROOT']."/api/account/account_user.php";
    $name = $_POST["name"];
    if(isset($_POST["password"]))
    {
        $password = $_POST["password"];
        $result = Account_User::login($name, $password);
        if($result == LOGIN_SUCCESS)
        {
            include_once $_SERVER['DOCUMENT_ROOT']."/api/application/application_token.php";
            $key = $_POST["API_KEY"];
            echo json_encode(array(
                "token" => Application_Token::createToken($key, $name)));
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
        $result = Account_User::getUserByName($name);
        if(count($result) == 1)
        {
            include_once $_SERVER['DOCUMENT_ROOT']."/api/application/application_token.php";
            $key = $_POST["API_KEY"];
            echo json_encode(array(
                "token" => Application_Token::createToken($key, $name)));
        }
        else
        {
            echo json_encode(array(
                "token" => "",
                "error" => "该用户不存在"));
        }
    }
}
?>
