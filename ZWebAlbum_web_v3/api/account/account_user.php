<?php
    include_once "account_regex.php";
    include_once $_SERVER['DOCUMENT_ROOT'].'/api/data/sql_user.php';

    define("USER_TYPE_NORMAL", 0);
    define("USER_TYPE_STAR", 1);
    define("USER_TYPE_VIP", 2);
    define("USER_TYPE_ADMIN", 3);
    define("USER_TYPE_SUPERADMIN", 4);

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
     * @def integer REGISTER_SUCCESS Register successfully.
     * @def integer REGISTER_ERROR_NAME The format of the name string is not valid.
     * @def integer REGISTER_ERROR_PASSWORD The format of the password string is not valid.
     * @def integer REGISTER_ERROR_NICKNAME The format of the nickname string is not valid.
     * @def integer REGISTER_ERROR_EXIST The user name is already exist.
     * @def integer REGISTER_ERROR_UNKNOWN An unknown error occured.
     */
    define("REGISTER_SUCCESS", 0);
    define("REGISTER_ERROR_NAME", -1);
    define("REGISTER_ERROR_PASSWORD", -2);
    define("REGISTER_ERROR_NICKNAME", -3);
    define("REGISTER_ERROR_EXIST", -4);
    define("REGISTER_ERROR_UNKNOWN", -5);
    /**
     * @def integer UPDATE_SUCCESS Update successfully.
     * @def integer UPDATE_FAILED Update failed, unknown sql matter.
     */
    define("UPDATE_SUCCESS", 0);
    define("UPDATE_FAILED", -1);
    
    /**
     * The APIs about user.
     * @author ZHG <CyberZHG@gmail.com>
     */
     class Account_User
     {

        public static function getTypeMessage($type)
        {
            switch($type)
            {
                case USER_TYPE_NORMAL:
                    return "Normal";
                case USER_TYPE_STAR:
                    return "Star";
                case USER_TYPE_VIP:
                    return "VIP";
                case USER_TYPE_ADMIN:
                    return "Admin";
                case USER_TYPE_SUPERADMIN:
                    return "Super Admin";
                default:
                    return "Unknown";
            }
        }

        /**
         * User login.
         * @param string $name The user name used to login.
         * @param string $password The password used to login.
         * @param string $sessionId The session id, use default when it's empty.
         * @return integer The pre-defined constants with prefix "LOGIN_".
         */
        public static function login($name, $password, $sessionId = "")
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
                    return LOGIN_ERROR_WRONG;
                }
                return LOGIN_ERROR_EXIST;
            }
            else
            {
                if($sessionId)
                {
                    session_start($sessionId);
                }
                else
                {
                    session_start();
                }
                $row = $result[0];
                $_SESSION['User_ID'] = $row['UserID'];
                $_SESSION['User_Name'] = $row['Name'];
                $_SESSION['User_Nickname'] = $row['Nickname'];
                $_SESSION['User_Type'] = $row['Type'];
                return LOGIN_SUCCESS;
            }
        }

        /**
         * Return the meaning of the login result.
         * @param int $result The result status of login.
         * @return string The meaning of the LOGIN_?
         */
        public static function getLoginMessage($result)
        {
            switch($result)
            {
                case LOGIN_SUCCESS:
                    return "登录成功";
                case LOGIN_ERROR_EXIST:
                    return "用户不存在";
                case LOGIN_ERROR_NAME:
                    return "用户名格式不正确";
                case LOGIN_ERROR_PASSWORD:
                    return "密码格式不正确";
                case LOGIN_ERROR_WRONG:
                    return "用户名或密码错误";
                default:
                    return "未知状态";
            }
        }
        
        /**
         * User logout.
         * @param string $sessionId The session id, use default when it's empty.
         */
        public static function logout($sessionId = "")
        {
            if($sessionId)
            {
                session_start($sessionId);
            }
            else
            {
                session_start();
            }
            session_destroy();
        }

        /**
         * Whether the password is correct.
         * @param string $name The user name used to login.
         * @param string $password The password used to login.
         * @return integer Return 1 if the password is correct, else return 0.
         */
        public static function isPasswordCorrect($name, $password)
        {
            $sql_user = new SQL_User();
            $result = $sql_user->selectByPassword($name, $password);
            if(count($result) == 1)
            {
                return 1;
            }
            return 0;
        }

        /**
         * Get user information by name.
         * @param string $name The name of the user.
         * @return array Query result.
         */
        public static function getUserByName($name)
        {
            $sql_user = new SQL_User();
            return $sql_user->selectByName($name);
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
         * @param array $user An associative array with "name", "password" and "nickname" keys.
         * @return integer Return constant with prefix "REGISTER_ERROR_" if register is failed, else return the user id.
         */
        public static function register($user)
        {
            // TODO Judge if the nickname contains any illegal words.
            $sql_user = new SQL_User();
            $result = $sql_user->selectByName($user["name"]);
            if(count($result) != 0)
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
         * Return the meaning of the register result.
         * @param int $result The result status of register.
         * @return string The meaning of the REGISTER_?
         */
        public static function getRegisterMessage($result)
        {
            switch($result)
            {
                case REGISTER_SUCCESS:
                    return "注册成功";
                case REGISTER_ERROR_NAME:
                    return "用户名格式不正确";
                case REGISTER_ERROR_PASSWORD:
                    return "密码格式不正确";
                case REGISTER_ERROR_EXIST:
                    return "用户名已经存在";
                case REGISTER_ERROR_NICKNAME:
                    return "用户昵称格式不正确";
                case REGISTER_ERROR_UNKNOWN:
                    return "未知错误";
                default:
                    return "未知状态";
            }
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
         * Return the meaning of the update result.
         * @param int $result The result status of update.
         * @return string The meaning of the UPDATE_?
         */
        public static function getUpdateMessage($result)
        {
            switch($result)
            {
                case UPDATE_SUCCESS:
                    return "更新成功";
                case UPDATE_FAILED:
                    return "更新失败";
            }
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
