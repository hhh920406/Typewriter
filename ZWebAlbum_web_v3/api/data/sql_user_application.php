<?php
    include_once "sql_define.php";
    include_once "sql_table.php";
    include_once "sql_query.php";

    /**
     * The SQL operation for user application table.
     * @author ZHG
     */
    class SQL_User_Application extends SQL_Table
    {
        /**
         * Change the table name.
         */
        public function __construct()
        {
            parent::__construct();
            $this->tableName = "D_User_Application";
            $this->primaryKeyName = "";
        }

        /**
         * Create the album table.
         */
        public function createTable()
        {
            $columns = array
            (
                "UserID"                =>  "INT(4) NOT NULL " . 
                                            "COMMENT 'The id of the user. '",
                "ApplicationID"         =>  "INT(4) NOT NULL " . 
                                            "COMMENT 'The id of the application. '",
                "Permission"            =>  "INT(4) NOT NULL " . 
                                            "COMMENT 'The permission of the user. '"
            );
            $primary = $this->primaryKeyName;
            $this->sql_query->createTable($this->tableName, $columns, $primary);
            $this->sql_query->alterForeignKey($this->tableName, "UserID", "D_User", "UserID");
        }

        /**
         * Select with user ID.
         * @param int $userID The id of the user.
         * @return array Query result. 
         */
        public function selectByUser($userID)
        {
            $condition = $this->getEqualCondition(array(
                    "UserID" => $userID
                ));
            $this->sql_query->select($this->tableName, "", $condition);
            return $this->sql_query->getAllResult();
        }
    }
?>
