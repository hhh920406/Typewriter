<?php
include_once "account_regex.php";
include_once $_SERVER['DOCUMENT_ROOT'].'/api/data/sql_user.php';

/**
 * The APIs about user.
 * @author ZHG
 */
 
 
/**
 * @def integer LOGIN_SUCCESS Successfully login, the session is saved.
 * @def integer LOGIN_ERROR_NAME The format of the name string is not valid.
 * @def integer LOGIN_ERROR_PASSWORD The format of the password string is not valid.
 * @def integer LOGIN_ERROR_EXIST The user name is not exist.
 * @def integer LOGIN_ERROR_WRONG The user name or password is not correct.
 */
define("LOGIN_SUCCESS", 0);
define("LOGIN_ERROR_NAME", -1);
define("LOGIN_ERROR_PASSWORD", -2);
define("LOGIN_ERROR_EXIST", -3);
define("LOGIN_ERROR_WRONG", -4);
/**
 * @def integer REGISTER_ERROR_NAME The format of the name string is not valid.
 * @def integer REGISTER_ERROR_PASSWORD The format of the password string is not valid.
 * @def integer REGISTER_ERROR_NICKNAME The format of the nickname string is not valid.
 * @def integer REGISTER_ERROR_EXIST The user name is already exist.
 * @def integer REGISTER_ERROR_UNKNOWN An unknown error occured.
 */
define("REGISTER_ERROR_NAME", -1);
define("REGISTER_ERROR_PASSWORD", -2);
define("REGISTER_ERROR_NICKNAME", -3);
define("REGISTER_ERROR_EXIST", -4);
define("REGISTER_ERROR_UNKNOWN", -5);

define("UPDATE_SUCCESS", 0);
define("UPDATE_FAILED", -1);

 class Account_User
 {

    /**
     * User login.
     * @param string $name The user name used to login.
     * @param string $password The password used to login.
     * @return integer The pre-defined constants with prefix "LOGIN_".
     */
    public static function login($name, $password)
    {
        if(!Account_Regex::isTextSimple($name))
        {
            return LOGIN_ERROR_NAME;
        }
        if(!Account_Regex::isTextSimple($password))
        {
            return LOGIN_ERROR_PASSWORD;
        }
        $sql_user = new SQL_User();
        $result = $sql_user->selectByPassword($name, $password);
        if(count($result) != 1)
        {
            $result = $sql_user->selectByName($name);
            if(count($result) == 1)
            {
                return ERROR_WRONG;
            }
            return ERROR_EXIST;
        }
        else
        {
            session_start();
            $row = $result[0];
            $_SESSION['User_ID'] = $row['UserID'];
            $_SESSION['User_Name'] = $row['Name'];
            $_SESSION['User_Nickname'] = $row['Nickname'];
            $_SESSION['User_Type'] = $row['Type'];
            return SUCCESS;
        }
    }

    /**
     * Judge if the user name is exist.
     * @param string $name The user name to be judged.
     * @return integer 1 as true, 0 as false.
     */
    public static function isUserNameExist($name)
    {
        $sql_user = new SQL_User();
        $result = $sql_user->selectByName($name);
        if(count($result) == 1)
        {
            return 1;
        }
        return 0;
    }

    /**
     * User register.
     * @param array $user An associative array with "name", "password" and "nickname" kyes.
     * @return integer Return constant with prefix "REGISTER_ERROR_" if register is failed, else return the user id.
     */
    public static function register($user)
    {
        // TODO Judge if the nickname contains any illegal words.
        $sql_user = new SQL_User();
        $result = $sql_user->selectByName($name);
        if(count($result) == 1)
        {
            return REGISTER_ERROR_EXIST;
        }
        if($sql_user->insert($user))
        {
            return $sql_user->getAutoIncrementID();
        }
        return REGISTER_ERROR_UNKNOWN;
    }
    
    /**
     * Update user basic information.
     * @param integer $id The user id whose information is to be updated.
     * @param array $user An associative array with "name", "password" and "nickname" keys.
     * @return integer UPDATE_SUCCESS if updated successfully, else UPDATE_FAILED.
     */
    public static function update($id, $user)
    {
        $sql_user = new SQL_User();
        if($sql_user->update($id, $user))
        {
            return UPDATE_SUCCESS;
        }
        return UPDATE_FAILED;
    }
    
    /**
     * Delete user.
     * @param integer $id The user id.
     */
    public static function delete($id)
    {
        $sql_user = new SQL_User();
        return $sql_user->delete($id);
    }
    
    /**
     * Get the total number of user.
     * @return integer The number of user.
     */
    public static function getUserNumber()
    {
        $sql_user = new SQL_User();
        return $sql_user->getRowNumber();
    }
    
    /**
     * Select user.
     * @param integer $itemsPerPage The number of items per page.
     * @param integer $pageNumber The page to be selected, the page index start with 1.
     * @return array An associative array with "id", "name", "password" and "nickname" keys.
     */
    public static function getUser($itemsPerPage, $pageNumber)
    {
        $sql_user = new SQL_User();
        return $sql_user->selectWithPage($itemsPerPage, $pageNumber);
    }
}
?>
