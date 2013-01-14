<?php
    include "sqlQuery.php";
    
    $databaseName = "Test";
    $tableName = "User_Test";
    
    function createTest()
    {
        global $databaseName;
        global $tableName;
        echo "CREATE Test";
        $database = new Database("", "", "", $databaseName);
        echo "<hr/>";
        
        echo "Create database: <br/>";
        $database->createDatabase($databaseName);
        echo $database->getQueryString();
        echo "<br/>";
        
        echo "Create table: <br/>";
        $typeArray = array( "ID" => "INT(4) NOT NULL AUTO_INCREMENT", 
                            "Name" => "VARCHAR(45) NOT NULL", 
                            "Password" => "VARCHAR(45) NOT NULL",
                            "Nickname" => "VARCHAR(45) DEFAULT ''",
                            "Type" => "INT(4) DEFAULT '0'");
        $primaryArray = array("ID");
        $database->createTable($tableName, $typeArray, $primaryArray);
        echo $database->getQueryString();
        echo "<br/>";
        echo "<hr/>";
    }

    function insertTest()
    {
        global $databaseName;
        global $tableName;
        echo "INSERT Test";
        $database = new Database("", "", "", $databaseName);
        echo "<hr/>";
        echo "Insert multiple: <br/>";
        $columnArray = array("Name", "Password", "Nickname", "Type");
        $valueArray = array(array("monkey015", "monkey", "无尽猴子十五号机", "0"), 
                            array("monkey016", "monkey", "无尽猴子十六号机", "0"), 
                            array("monkey017", "monkey", "无尽猴子十七号机", "0"));
        $database->insert($tableName, $columnArray, $valueArray);
        echo $database->getQueryString();
        echo "<br/>";
        echo "Insert single: <br/>";
        $valueArray = array("monkey018", "monkey", "无尽猴子十八号机", "0");
        $database->insert($tableName, $columnArray, $valueArray);
        echo $database->getQueryString();
        echo "<br/>";
        echo mysql_error();
        echo "<hr/>";
    }
    
    createTest();
    insertTest();
?>
