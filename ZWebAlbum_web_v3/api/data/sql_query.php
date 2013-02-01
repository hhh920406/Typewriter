<?php
include_once "sql_define.php";

/**
 * Provide basic operations for MySQL query.
 * It is not necessary to initial the connection manually before query.
 * To use SQL directly, just invoking the query function.
 * @author ZHG
 * @version 20130115
 */
class SQL_Query
{
    /**
     * @var string $host The host name of the database.
     * @var string $name The user name to connect to the host.
     * @var string $password The password to connect to the host.
     * @var string $databaseName he database name which to connect to.
     */
    private $host = HOST;
    private $name = NAME;
    private $password = PASSWORD;
    private $databaseName = DATABASE;

    /**
     * @var resource $connection The connection with the target database.
     * @var array $result The query result.
     * @var string $queryString The query string used when query undirectly.
     */
    private $connection = "";
    private $result = "";
    private $queryString = "";

    private static $instance = "";

    public static function getInstance()
    {
        if(SQL_Query::$instance == "")
        {
            SQL_Query::$instance = new SQL_Query();
        }
        return SQL_Query::$instance;
    }

    /**
     * Initial the class with database information.
     * @param string $host The host name.
     * @param string $name The login name.
     * @param string $password The login password.
     * @param string $databaseName The database name.
     */
    private function __construct($host = "", $name = "", $password = "", $databaseName = "")
    {
        if($host)
        {
            $this->host = $host;
        }
        if($name)
        {
            $this->name = $name;
        }
        if($password)
        {
            $this->password = $password;
        }
        if($databaseName)
        {
            $this->databaseName = $databaseName;
        }
        $this->init_connection();
    }

    /**
     * Close the connection to MySQL server.
     */
    public function __destruct()
    {
        $this->close_connection();
    }

    /**
     * Connect to MySQL server and set the charset to UTF-8
     */
    public function init_connection()
    {
        $this->connection = mysql_connect($this->host, $this->name, $this->password);
        if(!$this->connection)
        {
            die('Could not connect: ' . mysql_error());
        }
        mysql_select_db($this->databaseName, $this->connection);
        mysql_query("set names 'utf8'");
    }

    /**
     * Close the connection to MySQL server.
     */
    public function close_connection()
    {
        if($this->connection)
        {
            mysql_close($this->connection);
            $this->connection = "";
        }
    }

    /**
     * The basic SQL query.
     * @param string $queryString The SQL query.
     */
    public function query($queryString)
    {
        if(!$this->connection)
        {
            $this->init_connection();
        }
        $this->result = mysql_query($queryString, $this->connection);
    }

    /**
     * Get the row number of the query result.
     * @return integer The row number of the query result.
     */
    public function getRowNumber()
    {
        if($this->result)
        {
            return mysql_num_rows($this->result);
        }
        return 0;
    }

    /**
     * Get a single result from the query result.
     * @return array An associative array represents the result.
     */
    public function getSingleResult()
    {
        return mysql_fetch_array($this->result);
    }

    /**
     * Get the total query result.
     * @return array An associative array represents the integral query result.
     */
    public function getAllResult()
    {
        $rowsArray = array();
        while($row = mysql_fetch_array($this->result))
        {
            $rowsArray[] = $row;
        }
        return $rowsArray;
    }

    /**
     * Get the SQL query when query undirectly.
     * @return string The SQL query statement.
     */
    public function getQueryString()
    {
        return $this->queryString;
    }

    /**
     * Create a database in the host.
     * @param string $databaseName The database name to be created.
     */
    public function createDatabase($databaseName)
    {
        $this->queryString = "";
        if(!$databaseName)
        {
            return;
        }
        $this->queryString .= "CREATE DATABASE " . $databaseName . " ";
        $this->queryString .= "DEFAULT CHARACTER SET utf8 COLLATE utf8_unicode_ci;";
        $this->query($this->queryString);
    }

    /**
     * Create a table to the current database.
     * The function does not provide the error detection.
     * @param string $tableName The table name to be created.
     * @param array $columns An associative array, the keys represents the column names and the values represent the column types.
     * @param array $primaryKey When it is an array, it contains column names represents the primary keys. When it is a string, it presents the single primary key.
     */
    public function createTable($tableName, $columns, $primaryKey)
    {
        $this->queryString = "";
        $this->queryString .= "CREATE TABLE " . $tableName . "(";
        $space = 1;
        foreach($columns as $column => $type)
        {
            if($space)
            {
                $space = 0;
            }
            else
            {
                $this->queryString .= ", ";
            }
            $this->queryString .= $column . " " . $type;
        }
        if(is_array($primaryKey))
        {
            foreach($primaryKey as $primary)
            {
                $this->queryString .= ", ";
                $this->queryString .= "PRIMARY KEY (" . $primary . ")";
            }
        }
        else
        {
            if($primaryKey)
            {
                $this->queryString .= ", " . "PRIMARY KEY (" . $primaryKey . ")";
            }
        }
        $this->queryString .= ");";
        $this->query($this->queryString);
    }

    /**
     * Insert data to table.
     * The function does not provide the error detection.
     * @param string $tableName The table to be inserted.
     * @param array $columnArray An array of column names represents the correspondence between columns and values. When it is null it represents select all the columns with the table structure order.
     * @param array $valueArray When it is a one dimension array, it is the values to be inserted with the same order of the $columnArray. When it is a two dimensions array, it is a array of the one dimension array descriped just now.
     */
    public function insert($tableName, $columnArray, $valueArray)
    {
        $this->queryString = "";
        $this->queryString .= "INSERT INTO ";
        $this->queryString .= $tableName;
        if($columnArray)
        {
            $this->queryString .= "(";
            for($i = 0; $i < count($columnArray); ++ $i)
            {
                if($i)
                {
                    $this->queryString .= ", ";
                }
                $this->queryString .= $columnArray[$i];
            }
            $this->queryString .= ")";
        }
        $this->queryString .= " VALUES ";
        for($i = 0; $i < count($valueArray); ++ $i)
        {
            if($i)
            {
                $this->queryString .= ", ";
            }
            else
            {
                if(!is_array($valueArray[$i]))
                {
                    $this->queryString .= "(";
                    for($j = 0; $j < count($valueArray); ++ $j)
                    {
                        if($j)
                        {
                            $this->queryString .= ", ";
                        }
                        $this->queryString .= "'" . $valueArray[$j] . "'";
                    }
                    $this->queryString .= ")";
                    break;
                }
            }
            $this->queryString .= "(";
            for($j = 0; $j < count($valueArray[$i]); ++ $j)
            {
                if($j)
                {
                    $this->queryString .= ", ";
                }
                $this->queryString .= "'" . $valueArray[$i][$j] . "'";
            }
            $this->queryString .= ")";
        }
        $this->queryString .= ";";
        $this->query($this->queryString);
    }

    /**
     * Get the WHERE statement.
     * The function does not provide the error detection.
     * @param array $condition @see select
     * @param string $relation @see select
     * @return string The WHERE statement.
     */
    private function where($condition, $relation)
    {
        $sql = "";
        if($relation == "")
        {
            $relation = "AND";
        }
        if($condition)
        {
            $sql .= " WHERE ";
            if(is_array($condition))
            {
                for($i = 0; $i < count($condition); ++ $i)
                {
                    if($i)
                    {
                        $sql .= " " . $relation . " ";
                    }
                    $sql .= $condition[$i];
                }
            }
            else
            {
                $sql .= $condition;
            }
        }
        return $sql;
    }

    /**
     * Get the ORDER BY statement.
     * The function does not provide the error detection.
     * @param array $order @see select
     * @return string The ORDER BY statement.
     */
    private function orderby($order)
    {
        $sql = "";
        if($order)
        {
            $sql .= " ORDER BY ";
            if(is_array($order))
            {
                for($i = 0; $i < count($order); ++ $i)
                {
                    if($i)
                    {
                        $sql .= ", ";
                    }
                    $sql .= $order[$i];
                }
            }
            else
            {
                $sql .= $order;
            }
        }
        return $sql;
    }

    /**
     * Get the LIMIT statement.
     * @param array $limit @see select
     * @return string The LIMIT statement.
     */
    private function limit($limit)
    {
        $sql = "";
        if($limit)
        {
            $sql .= " LIMIT ";
            if(is_array($limit))
            {
                if(1 == count($limit))
                {
                    $sql .= $limit[0];
                }
                else if(2 == count($limit))
                {
                    $sql .= $limit[0] . ", " . $limit[1];
                }
            }
            else
            {
                $sql .= $limit;
            }
        }
        return $sql;
    }

    /**
     * Select data from table.
     * The function does not provide the error detection.
     * @param string $tableName The table to be selected.
     * @param array $columnNames The columns to be selected. If it is null, it is to select all the columns.
     * @param array $condition When it is a string, it presents the full WHERE SQL query string. When it is an array, it contains the conditions.
     * @param string $relation The $relation must be "AND" or "OR" if the $condtion is an array and its length is larger than one.
     * @param array $order When it is a string, it presents the single order condition. When it is an array, it contains the order conditions. If descent order is needed, append " DESC" to the end of column name.
     * @param array $limit When it is an integer, it is to choose $limit rows from the beginning. When is an array, it is to choose $limit[1] rows from $limit[0].
     */
    public function select($tableName, $columnNames, $condition = "", $relation = "", $order = "", $limit = "")
    {
        $this->queryString = "";
        $this->queryString .= "SELECT ";
        if($columnNames)
        {
            if(is_array($columnNames))
            {
                for($i = 0; $i < count($columnNames); ++ $i)
                {
                    if($i)
                    {
                        $this->queryString .= ", ";
                    }
                    $this->queryString .= "[" . $columnNames[$i] . "]";
                }
            }
            else
            {
                $this->queryString .= "[" . $columnNames . "]";
            }
        }
        else
        {
            $this->queryString .= "*";
        }
        $this->queryString .= " FROM ";
        $this->queryString .= $tableName;
        $this->queryString .= $this->where($condition, $relation);
        $this->queryString .= $this->orderby($order);
        $this->queryString .= $this->limit($limit);
        $this->queryString .= ";";
        $this->query($this->queryString);
    }

    /**
     * Count the number of selected data.
     * The function does not provide the error detection.
     * @param string $tableName The table to be selected.
     * @param array $columnNames The columns to be selected. If it is null, it is to select all the columns.
     * @param array $condition When it is a string, it presents the full WHERE SQL query string. When it is an array, it contains the conditions.
     * @param string $relation The $relation must be "AND" or "OR" if the $condtion is an array and its length is larger than one.
     */
    public function count($tableName, $columnNames, $condition = "", $relation = "")
    {
        $this->queryString = "";
        $this->queryString .= "SELECT COUNT(*) FROM ";
        $this->queryString .= $tableName;
        $this->queryString .= $this->where($condition, $relation);
        $this->queryString .= ";";
        $this->query($this->queryString);
    }

    /**
     * Update the data in table.
     * The function does not provide the error detection.
     * @param string $tableName The table where the data to be updated.
     * @param array $updateValue When it is an associative array, its keys represents the column names and its values represents the values to be updated to. When it is a string, it is just a standard SQL query.
     * @param array $condition @see select
     * @param string $relation @see select
     */
    public function update($tableName, $updateValue, $condition = "", $relation = "")
    {
        $this->queryString = "";
        $this->queryString .= "UPDATE ";
        $this->queryString .= $tableName;
        $this->queryString .= " SET ";
        if(is_array($updateValue))
        {
            $space = 1;
            foreach($updateValue as $column => $value)
            {
                if($space)
                {
                    $space = 0;
                }
                else
                {
                    $this->queryString .= ", ";
                }
                $this->queryString .= $column . " = '" . $value . "'";
            }
        }
        else
        {
            $this->queryString .= $updateValue;
        }
        $this->queryString .= $this->where($condition, $relation);
        $this->query($this->queryString);
    }

    /**
     * Delete data from table.
     * The function does not provide the error detection.
     * @param string $tableName The table where the data to be deleted.
     * @param array $condition @see select
     * @param string $relation @see select
     */
    public function delete($tableName, $condition = "", $relation = "")
    {
        $this->queryString = "";
        $this->queryString .= "DELETE FROM ";
        $this->queryString .= $tableName;
        $this->queryString .= $this->where($condition, $relation);
        $this->query($this->queryString);
    }
    
    /**
     * Add foreign key.
     * @param string $currentTableName
     * @param string $currentKeyName
     * @param string $foreignTableName
     * @param string $foreignKeyName
     * @param string $onDelete
     * @param string $onUpdate
     */
    public function alterForeignKey(
            $currentTableName, 
            $currentKeyName, 
            $foreignTableName, 
            $foreignKeyName, 
            $onDelete = "RESTRICT",
            $onUpdate = "RESTRICT")
    {
        $this->queryString = "ALTER TABLE ";
        $this->queryString .= $currentTableName . " ";
        $this->queryString .= "ADD FOREIGN KEY ";
        $this->queryString .= "(" . $currentKeyName . ") ";
        $this->queryString .= "REFERENCES ";
        $this->queryString .= $foreignTableName . " ";
        $this->queryString .= "(" . $foreignKeyName . ") ";
        $this->queryString .= "ON DELETE ";
        $this->queryString .= $onDelete . " ";
        $this->queryString .= "ON UPDATE ";
        $this->queryString .= $onUpdate;
        $this->query($this->queryString);
    }
}
?>
