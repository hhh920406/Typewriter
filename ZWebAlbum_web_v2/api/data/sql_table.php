<?php
class SQL_Table
{
    /*
     * @var resource $sql_query The SQL query object.
     */
    protected $sql_query = "";
    protected $tableName = "";
    protected $IDName = "";

    /**
     * Connect to SQL server.
     */
    public function __construct()
    {
        $this->sql_query = new SQL_Query();
    }

    /**
     * Release resouce.
     */
    public function __destroy()
    {
        unset($this->sql_query);
    }
    
    /**
     * Get the primary key name of the table.
     * @return string Primary key name.
     */
    public function getPrimaryKeyName()
    {
        return $this->IDName;
    }

    /**
     * Get the condition which all it contains is equal relation.
     * @param array $conditionArray The conditions.
     * @return string The final condition array.
     */
    protected function getEqualCondition($conditionArray)
    {
        $condition = array();
        foreach($conditionArray as $column => $value)
        {
            $condition[] = $column . " = '" . $value . "'";
        }
        return $condition;
    }

    /**
     * Select without LIMIT.
     * @param integer $startPosition The start position of the query result.
     * @param integer $rowNumber The row number of the query result.
     * @return array Query result.
     */
    public function selectWithLimit($startPosition = 0, $rowNumber = 30)
    {
        $limit = "";
        $limit = array($startPosition, $rowNumber);
        $this->sql_query->select($this->tableName, null, "", "", "", $limit);
        return $this->sql_query->getAllResult();
    }
    
    /**
     * Get the totol page number.
     * @param integer $itemsPerPage The number of items per page.
     * @return integer The page number.
     */
    public function getPageNumber($itemsPerPage)
    {
        return $this->getRowNumber() / $itemsPerPage;
    }
    
    /**
     * Select using page.
     * @param integer $itemsPerPage The number of items per page.
     * @param integer $pageNumber The page to be selected, the page index start with 1.
     * @return array Query result.
     */
    public function selectWithPage($itemsPerPage, $pageNumber)
    {
        return $this->selectWithLimit(($pageNumber - 1) * $itemsPerPage, $itemsPerPage);
    }

    /**
     * Get the total row number;
     * @return integer Row Number;
     */
    public function getRowNumber()
    {
        $this->sql_query->query("SELECT COUNT(*) FROM" . $this->tableName . ";");
        $result = $this->sql_query->getSingleResult();
        return $result[0];
    }

    /**
     * Select by ID.
     * @param int $ID
     * @return array Query result.
     */
    public function select($ID)
    {
        $condition = $this->getEqualCondition(array(
            $this->IDName => $ID
        ));
        $this->sql_query->select($this->tableName, "", $condition);
        return $this->sql_query->getAllResult();
    }

    /**
     * Insert new data.
     * @param type $info The associative array of the insert data.
     * @return int Return 0 if failed.
     */
    public function insert($info)
    {
        $columns = array();
        $values = array();
        foreach($info as $column => $value)
        {
            $columns[] = $column;
            $values[] = $value;
        }
        $this->sql_query->insert($this->tableName, $columns, $values);
        if(mysql_error())
        {
            return 0;
        }
        return 1;
    }

    /**
     * Update by ID.
     * @param type $ID
     * @param type $info The associative array represents the data to be updated.
     * @return int Return 0 if failed.
     */
    public function update($ID, $info)
    {
        $condition = $this->getEqualCondition(array(
            $this->IDName => $ID
        ));
        $this->sql_query->update($this->tableName, $info, $condition);
        if(mysql_error())
        {
            return 0;
        }
        return 1;
    }

    /**
     * Delete by ID.
     * @param type $ID
     * @return int Return 0 if failed.
     */
    public function delete($ID)
    {
        $condition = $this->getEqualCondition(array(
            $this->IDName => $ID
        ));
        $this->sql_query->delete($this->tableName, $condition);
        if(mysql_error())
        {
            return 0;
        }
        return 1;
    }

    /**
     * Get the lastest updated auto increment id.
     * @return int ID
     */
    public function getAutoIncrementID()
    {
        $this->sql_query->query("SELECT LAST_INSERT_ID()");
        $result = $this->sql_query->getSingleResult();
        return $result[0];
    }
}
?>
