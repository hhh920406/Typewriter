<?php
include "sql_define.php";
include "sql_table.php";
include "sql_query.php";

/**
 * The SQL operation for user table.
 * @author ZHG
 * @version 20130115
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
        $this->IDName = "UserID";
    }

    /**
     * Create the user table.
     */
    public function createTable()
    {
        $columns = array
        (
            $this->IDName => "INT(4) NOT NULL AUTO_INCREMENT",
            "Name" => "VARCHAR(45) NOT NULL UNIQUE",
            "Password" => "VARCHAR(45) NOT NULL",
            "Nickname" => "VARCHAR(45) DEFAULT ''",
            "Type" => "INT(4) DEFAULT '0'"
        );
        $primary = $this->IDName;
        $this->sql_query->createTable($this->tableName, $columns, $primary);

        $columns = array("Name", "Password", "Nickname", "Type");
        $values = array("MonkeyAdmin", "monkey", "猴子君主", "100");
        $this->sql_query->insert($this->tableName, $columns, $values);
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
