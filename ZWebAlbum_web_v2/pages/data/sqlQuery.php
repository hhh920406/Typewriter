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
        return mysql_fetch_array($this->result);
    }

    // 获取全部查询结果
    public function getAllResult()
    {
        $rowsArray = array();
        while($row = mysql_fetch_array($this->result))
        {
            $rowsArray[] = $row;
        }
        return $rowsArray;
    }

    // 返回间接SQL操作时的查询语句
    public function getQueryString()
    {
        return $this->queryString;
    }

    // 创建数据库
    // $databaseName是数据库名
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

    // 创建表
    // $tableName是表名
    // $typeArray是列名与类型的关联数组
    // $primaryArray是主键的数组
    public function createTable($tableName, $typeArray, $primaryArray)
    {
        $this->queryString = "";
        if(!$tableName || !$typeArray)
        {
            return;
        }
        $this->queryString .= "CREATE TABLE " . $tableName . "(";
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
    // $tableName对应表名
    // $columnArray是数据的列名
    // $valueArray是对应的数据
    public function insert($tableName, $columnArray, $valueArray)
    {
        $this->queryString = "";
        if(!$valueArray)
        {
            return;
        }
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
    
    // 获得条件判定的语句
    // $condition是一个关联数组，对应要比较的关系，如果为空则代表全部选择
    // $relation是$condition的相对关系，只取AND或OR
    private function where($condition, $relation)
    {
        if($condition)
        {
            if(count($condition) > 1 && $relation != "AND" && $relation != "OR")
            {
                return "ERROR";
            }
        }
        $sql = "";
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
    
    // 获得排序用的SQL语句
    // $order使用来排序的列，DESC在函数内不主动添加
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
    
    // 获得限定范围用的SQL语句
    // $limit是数据范围的限定
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

    // 数据库查询
    // $tableName对应表名
    // $columnNames对应要选择的列，如果为空则表示全部选择
    // $condition是一个关联数组，对应要比较的关系，如果为空则代表全部选择
    // $relation是$condition的相对关系，只取AND或OR
    // $order使用来排序的列，DESC在函数内不主动添加
    // $limit是数据范围的限定
    public function select($tableName, $columnNames, $condition, $relation = "", $order = "", $limit = "")
    {
        $this->queryString = "";
        if(!$tableName)
        {
            return;
        }
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
        $where = $this->where($condition, $relation);
        if($where == "ERROR")
        {
            return;
        }
        $this->queryString .= $where;
        $this->queryString .= $this->orderby($order);
        $this->queryString .= $this->limit($limit);
        $this->queryString .= ";";
        $this->query($this->queryString);
    }
}
?>
