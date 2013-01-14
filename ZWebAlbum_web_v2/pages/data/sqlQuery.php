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
    public function __construct($host = "", $name = "", $password = "", $databaseName = "")
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

    // 关闭数据库的连接
    public function close_connection()
    {
        mysql_close($connection);
    }

    // 进行基本的查询，结果保存到$result中
    public function query($queryString)
    {
        if(!$this->connection)
        {
            $this->init_connection();
        }
        $this->result = mysql_query($queryString, $this->connection);
    }

    // 获得上次查询返回的结果数
    public function getRowNumber()
    {
        return mysql_num_rows($this->result);
    }

    // 获取单条查询结果
    public function getSingleResult()
    {
        while($row = mysql_fetch_array($this->result))
        {
            return $row;
        }
    }

    // 获取全部查询结果
    public function getAllResult()
    {
        $rowsArray = array();
        while($row = mysql_fetch_array($this->result))
        {
            $rowsArray[] = $row;
        }
        return rowsArray;
    }

    // 返回间接SQL操作时的查询语句
    public function getQueryString()
    {
        return $this->queryString;
    }

    // 创建数据库，$databaseName是表名
    public function createDatabase($databaseName)
    {
        if(!$databaseName)
        {
            $this->queryString = "";
            return;
        }
        $this->queryString = "CREATE DATABASE " . $databaseName . " ";
        $this->queryString .= "DEFAULT CHARACTER SET utf8 COLLATE utf8_unicode_ci;";
        $this->query($this->queryString);
    }
    
    // 创建表
    // $tableName是表名
    // $typeArray是列名与类型的关联数组
    // $primaryArray是主键的数组
    public function createTable($tableName, $typeArray, $primaryArray)
    {
        if(!$tableName || !$typeArray)
        {
            $this->queryString = "";
            return;
        }
        $this->queryString = "CREATE TABLE " . $tableName . "(";
        $space = 1;
        foreach($typeArray as $column => $type)
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
        foreach($primaryArray as $primary)
        {
            $this->queryString .= ", ";
            $this->queryString .= "PRIMARY KEY (" . $primary . ")";
        }
        $this->queryString .= ");";
        $this->query($this->queryString);
    }
    
    // 插入数据
    // $columnArray是数据的列名
    // $valueArray是对应的数据
    public function insert($tableName, $columnArray, $valueArray)
    {
        if(!$valueArray)
        {
            $this->queryString = "";
            return;
        }
        $this->queryString = "INSERT INTO ";
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

    function select($columnNames, $tableName, $relation, $order, $limit)
    {
    }
}
?>
