<?php
include_once "sql_define.php";
include_once "sql_table.php";
include_once "sql_query.php";

/**
 * The SQL operation for user table.
 * @author ZHG
 */
class SQL_User extends SQL_Table
{
    /**
     * Change the table name.
     */
    public function __construct()
    {
        parent::__construct();
        $this->tableName = "D_User";
        $this->primaryKeyName = "UserID";
    }

    /**
     * Create the user table.
     */
    public function createTable()
    {
        $columns = array
        (
            $this->primaryKeyName   =>  "INT(4) NOT NULL AUTO_INCREMENT " . 
                                        "COMMENT 'The ID of the user. '",
            "Name"                  =>  "VARCHAR(45) NOT NULL UNIQUE " . 
                                        "COMMENT 'The login name of the user. '",
            "Password"              =>  "VARCHAR(45) NOT NULL " . 
                                        "COMMENT 'The login password of the user. '",
            "Nickname"              =>  "VARCHAR(45) DEFAULT '' " . 
                                        "COMMENT 'The nickname of the user. '",
            "Type"                  =>  "INT(4) DEFAULT '0' " . 
                                        "COMMENT 'The type of the user. '"
        );
        $primary = $this->primaryKeyName;
        $this->sql_query->createTable($this->primaryKeyName, $columns, $primary);

        $columns = array("Name", "Password", "Nickname", "Type");
        $values = array("MonkeyAdmin", "monkey", "猴子君主", "100");
        $this->sql_query->insert($this->primaryKeyName, $columns, $values);
    }

    /**
     * Select by Name.
     * @param string $Name
     * @return array Query result.
     */
    public function selectByName($Name)
    {
        $condition = $this->getEqualCondition(array(
            "Name" => $Name
        ));
        $this->sql_query->select($this->tableName, "", $condition);
        return $this->sql_query->getAllResult();
    }

    /**
     * Select by Name and Password.
     * @param string $Name
     * @param string $Password
     * @return array Query result.
     */
    public function selectByPassword($Name, $Password)
    {
        $condition = $this->getEqualCondition(array(
            "Name" => $Name,
            "Password" => $Password
        ));
        $this->sql_query->select($this->tableName, "", $condition, "AND");
        return $this->sql_query->getAllResult();
    }
}
?>
