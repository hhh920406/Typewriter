<?php
    include_once "sql_define.php";
    include_once "sql_table.php";
    include_once "sql_query.php";

    /**
     * The SQL operation for application token table.
     * @author ZHG
     */
    class SQL_Application_Token extends SQL_Table
    {
        /**
         * Change the table name.
         */
        public function __construct()
        {
            parent::__construct();
            $this->tableName = "D_Application_Token";
            $this->primaryKeyName = "";
        }

        /**
         * Create the table.
         */
        public function createTable()
        {
            $columns = array
            (
                "APIKey"    =>  "VARCHAR(32) NOT NULL " .
                                "COMMENT 'The API key of the application. '",
                "UserName"  =>  "VARCHAR(50) NOT NULL " .
                                "COMMENT 'The name of the user. '",
                "Token"     =>  "VARCHAR(32) NOT NULL " .
                                "COMMENT 'The communication token. '"
            );
            $primary = $this->primaryKeyName;
            $this->sql_query->createTable($this->tableName, $columns, $primary);
        }

        /**
         * Select by the token.
         * @param string $token
         * @return array Query result.
         */
        public function selectByToken($token)
        {
            $condition = $this->getEqualCondition(array(
                "Token" => $token
            ));
            $this->sql_query->select($this->tableName, "", $condition);
            return $this->sql_query->getAllResult();
        }

        /**
         * Select by the API key and user name.
         * @param string $key The API key.
         * @param string $name The name of user.
         * @return array Query result.
         */
        public function selectByKeyAndName($key, $name)
        {
            $condition = $this->getEqualCondition(array(
                "APIKey" => $key,
                "UserName" => $name
            ));
            $this->sql_query->select($this->tableName, "", $condition);
            return $this->sql_query->getAllResult();
        }

        /**
         * Delete by the API key and user name.
         * @param string $key The API key.
         * @param string $name The name of user.
         */
        public function deleteByKeyAndName($key, $name)
        {
            $condition = $this->getEqualCondition(array(
                "APIKey" => $key,
                "UserName" => $name
            ));
            $this->sql_query->delete($this->tableName, $condition);
        }

        /**
         * Insert a new token.
         * @param string $key The API key of the application.
         * @param string $name The name of the user.
         * @return string The new token.
         */
        public function insertToken($key, $name)
        {
            $token = substr(md5(uniqid(mt_rand(), true)), 0, 32);
            $columnArray = array("APIKey", "UserName", "Token");
            $valueArray = array($key, $name, $token);
            $this->sql_query->insert($this->tableName, $columnArray, $valueArray);
            return $token;
        }
    }
?>
