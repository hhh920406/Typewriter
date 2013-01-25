<?php
    include_once "sql_define.php";
    include_once "sql_table.php";
    include_once "sql_query.php";

    /**
     * The SQL operation for application table.
     * @author ZHG
     */
    class SQL_Application_Permission extends SQL_Table
    {
        /**
         * Change the table name.
         */
        public function __construct()
        {
            parent::__construct();
            $this->tableName = "D_Application_Permission";
            $this->primaryKeyName = "";
        }

        /**
         * Create the album table.
         */
        public function createTable()
        {
            $columns = array
            (
                "ApplicationID" =>  "INT(4) NOT NULL " . 
                                    "COMMENT 'The ID of application. '",
                "Permission"    =>  "INT(4) NOT NULL " . 
                                    "COMMENT 'The type of the permission. '",
                "Type"          =>  "INT(4) DEFAULT '0' " . 
                                    "COMMENT 'The needs of the permission. '"
            );
            $primary = $this->primaryKeyName;
            $this->sql_query->createTable($this->tableName, $columns, $primary);
            $this->sql_query->alterForeignKey($this->tableName, "ApplicationID", "D_Application", "ApplicationID");
        }

        /**
         * Select with application ID.
         * @param int $applicationID The id of the application.
         * @return array Query result. 
         */
        public function selectByApplication($applicationID)
        {
            $condition = $this->getEqualCondition(array(
                    "ApplicationID" => $applicationID
                ));
            $this->sql_query->select($this->tableName, "", $condition);
            return $this->sql_query->getAllResult();
        }
    }
?>
