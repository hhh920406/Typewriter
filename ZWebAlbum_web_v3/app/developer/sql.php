<?php

define("HOST", "localhost");
define("NAME", "ZHG");
define("PASSWORD", "19910702");
define("DATABASE", "ZWebAlbum_v3");

class SQL {
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

    /**
     * Initial the class with database information.
     * @param string $host The host name.
     * @param string $name The login name.
     * @param string $password The login password.
     * @param string $databaseName The database name.
     */
    public function __construct($host = "", $name = "", $password = "", $databaseName = "") {
        if($host) {
            $this->host = $host;
        }
        if($name) {
            $this->name = $name;
        }
        if($password) {
            $this->password = $password;
        }
        if($databaseName) {
            $this->databaseName = $databaseName;
        }
        $this->init_connection();
    }

    /**
     * Close the connection to MySQL server.
     */
    public function __destruct() {
        $this->close_connection();
    }

    /**
     * Connect to MySQL server and set the charset to UTF-8
     */
    public function init_connection() {
        $this->connection = mysql_connect($this->host, $this->name, $this->password);
        if(!$this->connection) {
            die('Could not connect: ' . mysql_error());
        }
        mysql_select_db($this->databaseName, $this->connection);
        mysql_query("set names 'utf8'");
    }

    /**
     * Close the connection to MySQL server.
     */
    public function close_connection() {
        if($this->connection) {
            mysql_close($this->connection);
        }
    }

    /**
     * The basic SQL query.
     * @param string $queryString The SQL query.
     */
    public function query($queryString) {
        if(!$this->connection) {
            $this->init_connection();
        }
        $this->result = mysql_query($queryString, $this->connection);
    }

    /**
     * Get the row number of the query result.
     * @return integer The row number of the query result.
     */
    public function getRowNumber() {
        if($this->result) {
            return mysql_num_rows($this->result);
        }
        return 0;
    }

    /**
     * Get a single result from the query result.
     * @return array An associative array represents the result.
     */
    public function getSingleResult() {
        return mysql_fetch_array($this->result);
    }

    /**
     * Get the total query result.
     * @return array An associative array represents the integral query result.
     */
    public function getAllResult() {
        $rowsArray = array();
        while($row = mysql_fetch_array($this->result)) {
            $rowsArray[] = $row;
        }
        return $rowsArray;
    }
}
?>
