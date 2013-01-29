<?php
include_once $_SERVER["DOCUMENT_ROOT"] . "/api/data/sql_application_token.php";

/**
 * Basic operations for application token distribution.
 * @author ZHG <CyberZHG@gmail.com>
 */
class Application_Token
{
    /**
     * Create a new token.
     * @param string $key The API key of the application.
     * @param string $name The name of the user.
     * @return string The application token.
     */
    public static function createToken($key, $name)
    {
        $sql = new SQL_Application_Token();
        $result = $sql->selectByKeyAndName($key, $name);
        if(count($result) > 0)
        {
            $sql->deleteByKeyAndName($key, $name);
        }
        return $sql->insertToken($key, $name);
    }

    /**
     * Get the user name.
     * @param string $token The token of the communication.
     * @return string The user name.
     */
    public static function getUserName($token)
    {
        $sql = new SQL_Application_Token();
        $result = $sql->selectByToken($token);
        if(count($result) > 0)
        {
            foreach($result as $row)
            {
                return $row["UserName"];
            }
        }
        return "";
    }

    /**
     * Get the user ID.
     * @param string $token The token of the communication.
     * @return string The user ID.
     */
    public static function getUserID($token)
    {
        $sql = new SQL_Application_Token();
        $result = $sql->selectByToken($token);
        if(count($result) > 0)
        {
            foreach($result as $row)
            {
                return $row["UserID"];
            }
        }
        return "";
    }

    /**
     * Get the API key.
     * @param string $token The token of the communication.
     * @return string The API key.
     */
    public static function getAPIKey($token)
    {
        $sql = new SQL_Application_Token();
        $result = $sql->selectByToken($token);
        if(count($result) > 0)
        {
            foreach($result as $row)
            {
                return $row["APIKey"];
            }
        }
        return "";
    }
}
?>
