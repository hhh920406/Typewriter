<!DOCTYPE html>

<html>
    <head>
        <meta charset = "utf-8">
        <title>Application_Session</title>
    </head>
    
    <body>
        <?php
            include_once $_SERVER['DOCUMENT_ROOT'].'/api/account/account_user.php';
            /**
             * The page is used for the login of user. 
             * The page returns nothing when there is no query string.
             * The page echos a new session id when query with "apikey" only.
             * The page echos "SUCCESSED" when the user is already login, and query with "apikey" and "session".
             * The page echos "SUCCESSED" when query with "apikey", "session", "name", "password".
             */
            if(isset($_GET["apikey"]))
            {
                if(isset($_GET["session"]))
                {
                    $session = $_GET["session"];
                    session_start($session);
                    if(isset($_GET["name"]) && isset($_SET["password"]))
                    {
                        $name = $_GET["name"];
                        $password = $_GET["password"];
                        $result = Account_User::login($name, $password, $session);
                        if($result == LOGIN_SUCCESS)
                        {
                            echo "SUCCESSED";
                        }
                        else
                        {
                            switch($result)
                            {
                                case LOGIN_ERROR_NAME:
                                    echo "用户名格式不合法";
                                    break;
                                case LOGIN_ERROR_PASSWORD:
                                    echo "密码格式不合法";
                                    break;
                                case LOGIN_ERROR_EXIST:
                                    echo "用户名不存在";
                                    break;
                                case LOGIN_ERROR_WRONG:
                                    echo "用户名或密码错误";
                                    break;
                            }
                        }
                    }
                    else
                    {
                        if($_SESSION["User_ID"])
                        {
                            echo "SUCCESSED";
                        }
                    }
                }
            }
            else
            {
                session_start();
                echo session_id();
            }    
        ?>
    </body>
</html>
