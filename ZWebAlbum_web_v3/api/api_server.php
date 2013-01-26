<?php
if(isset($_POST["method"]))
{
    switch($_POST["method"])
    {
        case "token":
            if(isset($_POST["name"]))
            {
                include_once "account/account_user.php";
                $name = $_POST["name"];
                if(isset($_POST["password"]))
                {
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
                    $result = Account_User::getUserByName($name);
                    if(count($result) == 1)
                    {
                        session_start();
                        $row = $result[0];
                        $_SESSION['User_ID'] = $row['UserID'];
                        $_SESSION['User_Name'] = $row['Name'];
                        $_SESSION['User_Nickname'] = $row['Nickname'];
                        $_SESSION['User_Type'] = $row['Type'];
                        echo json_encode(array(
                            "token" => session_id()));
                    }
                    else
                    {
                        echo json_encode(array(
                            "token" => "",
                            "error" => "该用户不存在"));
                    }
                }
            }
            break;
    }
}
?>
