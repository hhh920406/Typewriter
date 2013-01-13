<?php
/**
* 提供数据库连接的基本方式
*/
class Database
{
    private $host = "localhost";            // 主机名
    private $name = "ZHG";                  // 登录名
    private $password = "19910702";         // 登录密码
    private $databaseName = "ZWebAlbum_v2"; // 数据库名
    
    private $connection = "";   // 连接
    private $result = "";       // 查询结果
    private $queryString = "";  // 用于查询的字符串，在使用间接SQL语句时使用
    
    // 构造函数，初始化数据库连接。如果不传递参数则使用默认配置。
    function __construct($host = "", $name = "", $password = "", $databaseName = "")
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
    
    // 初始化数据库的连接并把字符设为UTF8
    function init_connection()
    {
        $this->connection = mysql_connect($this->host, $this->name, $this->password);
        if(!$this->connection)
        {
            die('Could not connect: ' . mysql_error());
        }
        mysql_select_db($this->databaseName, $this->connection);
        mysql_query("set names 'utf8'");
    }
    
    // 关闭数据库的连接
    function close_connection()
    {
        mysql_close($connection);
    }
    
    // 进行基本的查询，结果保存到$result中
    function query($queryString)
    {
        if(!$this->connection)
        {
            $this->init_connection();
        }
        $this->result = mysql_query($queryString, $this->connection);
    }
    
    // 获得上次查询返回的结果数
    function getRowNumber()
    {
        return mysql_num_rows($this->result);
    }
    
    // 获取单条查询结果
    function getSingle()
    {
        while($row = mysql_fetch_array($this->result))
        {
            return $row;
        }
    }
    
    // 获取全部查询结果
    function getArray()
    {
        $rowsArray = array();
        while($row = mysql_fetch_array($this->result))
        {
            $rowsArray[] = $row;
        }
        return rowsArray;
    }
    
    function getQueryString()
    {
        return $this->queryString;
    }
    
    // 创建数据库，$databaseName是表名
    function createDatabase($databaseName)
    {
        $this->queryString = "CREATE DATABASE " . $databaseName . " ";
        $this->queryString .= "DEFAULT CHARACTER SET utf8 COLLATE utf8_unicode_ci;";
        $this->query($this->queryString);
    }
    
    // 创建表，$tableName是表名，$typeArray是列名与类型的关联数组
    function createTableArray1($tableName, $typeArray)
    {
        $columns = array();
        $types = array();
        foreach ($typeArray as $column => $type)
        {
            $columns[] = $column;
            $types[] = $type;
        }
        $this->createTableArray2($tableName, $columns, $types);
    }
    
    // 创建表，$tableName是表名，$columnArray是列名数组，$typeArray是关联数组
    function createTableArray2($tableName, $columnArray, $typeArray)
    {
        $this->queryString = "CREATE TABLE " . $tableName . "(";
        for ($i=0;$i<count($columnArray);++$i)
        {
            if ($i)
            {
                $this->queryString .= ", ";
            }
            $this->queryString .= $columnArray[$i] . " " . $typeArray[$i];
        }
        $this->queryString .= ");";
        $this->query($this->queryString);
    }
    
    // 用于返回将数组中的值连接后的字符串。
    // $bracketLeft和$bracketRight是字符串两侧的括号
    // $separate是用于分隔值的字符串
    // $quotation是用来限定值的引号
    private function connectValues($array, $bracketLeft = "(", $bracketRight = ") ", $separate = ", ", $quotation = "'")
    {
        $result = $bracketLeft;
        for ($i=0;$i<count($array);++$i)
        {
            if ($i)
            {
                $result .= $separate;
            }
            $result .= $quotation . $array[$i] . $quotation;
        }
        $result .= $bracketRight;
        return $result;
    }
    
    // 插入单条数据
    // $valueArray是值的关联数组
    function insertSingleArray1($tableName, $valueArray)
    {
        $columns = array();
        $values = array();
        foreach ($valueArray as $column => $value)
        {
            $columns[] = $column;
            $values[] = $value;
        }
        $this->insertSingleArray2($tableName, $columns, $values);
    }
    
    // 插入单条数据
    // $valueArray是值的关联数组的数组
    function insertMultipleArray1($tableName, $valueArray)
    {
        if (0 == count($valueArray))
        {
            $this->queryString = "";
            return;
        }
        $columns = array();
        $values = array();
        for ($i=0;$i<count($valueArray);++$i)
        {
            if (0 == $i)
            {
                foreach ($valueArray[0] as $column => $value)
                {
                    $columns[] = $column;
                }
            }
            $lineValue = array();
            foreach ($valueArray[$i] as $column => $value)
            {
                $lineValue[] = $value;
            }
            $values[] = $lineValue;
        }
        $this->insertMultipleArray2($tableName, $columns, $values);
    }
    
    // 插入单条数据
    // $columnNames是与插入值对应的列名
    // $valueArray是插入值
    function insertSingleArray2($tableName, $columnNames, $valueArray)
    {
        $this->queryString = "INSERT INTO ";
        $this->queryString .= $tableName;
        $this->queryString .= " ";
        $this->queryString .= $this->connectValues($columnNames, "(", ") ", ",", "");
        $this->queryString .= "VALUES ";
        $this->queryString .= $this->connectValues($valueArray);
        $this->queryString .= ";";
        $this->query($this->queryString);
    }
    
    // 插入单条数据
    // $columnNames是与插入值对应的列名
    // $valueArray是插入值的二维数组
    function insertMultipleArray2($tableName, $columnNames, $valueArray)
    {
        if (0 == count($valueArray))
        {
            $this->queryString = "";
            return;
        }
        $this->queryString = "INSERT INTO ";
        $this->queryString .= $tableName;
        $this->queryString .= " ";
        $this->queryString .= $this->connectValues($columnNames, "(", ") ", ",", "");
        $this->queryString .= "VALUES ";
        for($i=0;$i<count($valueArray);++$i)
        {
            if ($i)
            {
                $this->queryString .= ", ";
            }
            $this->queryString .= $this->connectValues($valueArray[$i]);
        }
        $this->queryString .= ";";
        $this->query($this->queryString);
    }
}
?>
