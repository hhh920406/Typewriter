<?php
class Database
{
    private $host = "localhost";
    private $name = "ZHG";
    private $password = "19910702";
    private $databaseName = "ZWebAlbum_v2";
    
    private $connection = "";
    private $result = "";
    
    function __construct()
    {
        $this->init_connection();
    }
    
    function init_connection()
    {
        $this->connection = mysql_connect($this->host, $this->name, $this->password);
        if(!$this->connection)
        {
            die('Could not connect: ' . mysql_error());
        }
        mysql_select_db($this->databaseName, $this->connection);
        mysql_query("set names utf-8");
    }
    
    function close_connection()
    {
        mysql_close($connection);
    }
    
    function query($queryString)
    {
        if(!$this->connection)
        {
            $this->init_connection();
        }
        $this->result = mysql_query($queryString, $this->connection);
    }
    
    function getRowNumber()
    {
        return mysql_num_rows($this->result);
    }
    
    function getSingle()
    {
        while($row = mysql_fetch_array($this->result))
        {
            return $row;
        }
    }
    
    function getArray()
    {
        $rowsArray = array();
        while($row = mysql_fetch_array($this->result))
        {
            $rowsArray[] = $row;
        }
        return rowsArray;
    }
}
?>