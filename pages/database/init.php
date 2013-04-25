<!DOCTYPE html>
<html>
    <head>
        <meta charset = UTF-8>
        <title>数据库初始化</title>
    </head>
    <body>
        <?php
        /**
         * 用来进行程序所需数据库的初始化。
         * @author ZHG <CyberZHG@gmail.com>
         */
        require_once "SQLQuery.class.php";
        
        /**
         * 获取表是否存在的查询语句。
         * @param string $tableName 表名。
         * @reutrn string 查询语句。
         */
        function getTableExistanceString($tableName) {
            return "SELECT * " . 
                   "FROM INFORMATION_SCHEMA.TABLES " . 
                   "WHERE TABLE_NAME = '" . $tableName . "' " . 
                   "and TABLE_SCHEMA = '" . SQL_DATABASE . "';";
        }

        $sql = SQLQuery::getInstance();
        echo "<h1>数据库初始化</h1>";
        echo "<hr/>";
        require_once "init_database.php";
        require_once "init_table.php";
        ?>
    </body>
</html>

