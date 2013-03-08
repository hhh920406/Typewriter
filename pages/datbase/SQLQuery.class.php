<?php
/**
 * 基本的MySQL数据库封装。
 * @author ZHG <CyberZHG@gmail.com>
 */
require_once "setting.php";

class SQLQuery {
    protected $host = SQL_HOST; /**MySQL服务器地址。*/
    protected $name = SQL_NAME; /**登录名。*/
    protected $password = SQL_PASSWORD; /**密码。*/
    protected $database = SQL_DATABASE; /**数据库名。*/
    
    protected $connection = ""; /**数据区连接状态。*/
    protected $result = ""; /**查询返回结果。*/
    
    private static $instance = ""; /**单例的句柄。*/
    
    /**
     * 获取数据库连接的单例。
     * @return SQLQuery 返回当前类的实例。
     */
    public static function getInstance() {
        if ("" === SQLQuery::$instance) {
            SQLQuery::$instance = new SQLQuery();
        }
        return SQLQuery::$instance;
    }
    
    /**
     * 构造函数。
     */
    private function __construct() {
        $this->initConnection();
    }
    
    /**
     * 析构函数。
     */
    public function __destruct() {
        $this->closeConnection();
    }
    
    /**
     * 创建数据库的连接。
     */
    public function initConnection() {
        $this->closeConnection();
        $this->connection = mysql_connect($this->host, $this->name, $this->password);
        if (!$this->connection) {
            die("Could not connect to database: " . mysql_error());
        }
        mysql_select_db($this->database, $this->connection);
        mysql_query("set names 'utf8'");
    }
    
    /**
     * 关闭数据库的连接。
     */
    public function closeConnection() {
        if ($this->connection) {
            mysql_close($this->connection);
            $this->connection = "";
        }
    }
    
    /**
     * 进行数据库的查询操作。
     * @param string $query SQL语句。
     */
    public function query($query) {
        if (!$this->connection) {
            $this->initConnection();
        }
        $this->result = mysql_query($query, $this->connection);
    }
    
    /**
     * 获取查询的结果。
     * @return array 结果以行为单位的数组。
     */
    public function getResult() {
        $rows = array();
        while ($row = mysql_fetch_array($this->result)) {
            $rows[] = $row;
        }
        return $rows;
    }
    
    /**
     * 返回查询中出现的错误信息。
     * @return string 错误信息。
     */
    public function getError() {
        return mysql_error();
    }
}

?>
