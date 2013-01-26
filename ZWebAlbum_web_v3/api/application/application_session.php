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
             * The page returns nothing without the query string "apikey".
             * The page echos a new session id when query with "apikey" only and the user is already login.
             * The page echos "SUCCESSED" when the user is already login, and query with "apikey" and "session".
             * The page echos "SUCCESSED" when query with "apikey", "name", "password".
             */
            if(isset($_GET["apikey"]))
            {
                if(isset($_GET["session"]))
                {
                    $session_id = $_GET["session"];
                    session_start($session_id);
                    if(isset($_GET["User_ID"]))
                    {
                        echo "SUCCESSED";
                    }
                }
                else
                {
                    if(isset($_GET["name"]) && isset($_GET["password"]))
                    {
                        $name = $_GET["name"];
                        $password = $_GET["password"];
                        $result = Account_User::login($name, $password, $session);
                        if($result == LOGIN_SUCCESS)
                        {
                            echo "SUCCESSED_" + session_id();
                        }
                        else
                        {
                            echo Account_User::getLoginString($result);
                        }
                    }
                }
            }
        ?>
    </body>
</html>
