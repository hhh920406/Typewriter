<?php
    include_once "sql_define.php";
    include_once "sql_table.php";
    include_once "sql_query.php";

    /**
     * The SQL operation for album table.
     * @author ZHG
     */
    class SQL_Album extends SQL_Table
    {
        /**
         * Change the table name.
         */
        public function __construct()
        {
            parent::__construct();
            $this->tableName = "D_Album";
            $this->primaryKeyName = "AlbumID";
        }

        /**
         * Create the album table.
         */
        public function createTable()
        {
            $columns = array
            (
                $this->primaryKeyName   =>  "INT(4) NOT NULL AUTO_INCREMENT " . 
                                            "COMMENT 'The ID of album. '",
                "UserID"                =>  "INT(4) NOT NULL " . 
                                            "COMMENT 'The ID of the user who owns the album. '",
                "Name"                  =>  "VARCHAR(50) UNIQUE NOT NULL " . 
                                            "COMMENT 'The name of the album. '",
                "Description"           =>  "VARCHAR(200) DEFAULT '' " . 
                                            "COMMENT 'The Description of the album. '",
                "PhotoPath"             =>  "TEXT " . 
                                            "COMMENT 'The cover photo path of the album. '",
                "Type"                  =>  "INT(4) DEFAULT '0' " . 
                                            "COMMENT 'The type of the album. '",
                "Indice"                 =>  "INT(4) DEFAULT '0' " . 
                                            "COMMENT 'The value used to sort. '"
            );
            $primary = $this->primaryKeyName;
            $this->sql_query->createTable($this->tableName, $columns, $primary);
            $this->sql_query->alterForeignKey($this->tableName, "UserID", "D_User", "UserID");
        }

        /**
         * Select by Name.
         * @param string $Name
         * @return array Query result.
         */
        public function selectByName($userID, $Name)
        {
            $condition = $this->getEqualCondition(array(
                "UserID" => $userID,
                "Name" => $Name
            ));
            $this->sql_query->select($this->tableName, "", $condition);
            return $this->sql_query->getAllResult();
        }

        /**
         * Select by UserID.
         * @param integer $UserID
         * @return array Query result.
         */
        public function selectByUser($userID)
        {
            $condition = $this->getEqualCondition(array(
                "UserID" => $userID
            ));
            $this->sql_query->select($this->tableName, "", $condition, "", "Indice DESC");
            return $this->sql_query->getAllResult();
        }
    }
?>
