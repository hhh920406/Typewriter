<?php
    include_once "sql_define.php";
    include_once "sql_table.php";
    include_once "sql_query.php";

    define("TYPE_APP_INSIDE", 1);
    define("TYPE_APP_OUTSIDE", 2);
    define("TYPE_APP_DESKTOP", 3);
    define("TYPE_APP_CORE", 4);

    /**
     * The SQL operation for application table.
     * @author ZHG
     */
    class SQL_Application extends SQL_Table
    {
        /**
         * Change the table name.
         */
        public function __construct()
        {
            parent::__construct();
            $this->tableName = "D_Application";
            $this->primaryKeyName = "ApplicationID";
        }

        /**
         * Create the album table.
         */
        public function createTable()
        {
            $columns = array
            (
                $this->primaryKeyName   =>  "INT(4) NOT NULL AUTO_INCREMENT " . 
                                            "COMMENT 'The ID of application. '",
                "UserID"                =>  "INT(4) NOT NULL " . 
                                            "COMMENT 'The ID of the user who create the application. '",
                "APIKey"                =>  "VARCHAR(32) UNIQUE NOT NULL " . 
                                            "COMMENT 'The API key of the application. '",
                "Symbol"                =>  "VARCHAR(32) UNIQUE NOT NULL " .
                                            "COMMENT 'The symbol for distinction. '",
                "Name"                  =>  "VARCHAR(50) NOT NULL " . 
                                            "COMMENT 'The name of the application'",
                "Description"           =>  "VARCHAR(240) DEFAULT '' " .
                                            "COMMENT 'The Description of the photo. '",
                "Type"                  =>  "INT(4) DEFAULT '0' " . 
                                            "COMMENT 'The type of the applicaiton. '"
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

        /**
         * Select by the application symbol.
         * @param string $symbol The application symbol.
         * @return array Query result.
         */
        public function selectBySymbol($symbol)
        {
            $condition = $this->getEqualCondition(array(
                "Symbol" => $symbol
            ));
            $this->sql_query->select($this->tableName, "", $condition);
            return $this->sql_query->getAllResult();
        }
    }
?>
