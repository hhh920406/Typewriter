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
                            "PRIMARY KEY" => "(ID)",
                            "Name" => "VARCHAR(45) NOT NULL", 
                            "Password" => "VARCHAR(45) NOT NULL",
                            "Nickname" => "VARCHAR(45) DEFAULT ''",
                            "Type" => "INT(4) DEFAULT '0'");
        $database->createTableArray1($tableName, $typeArray);
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
        
        echo "Insert single data: <br/>";
        $valueArray = array("Name" => "monkey005", 
                            "Password" => "monkey", 
                            "Nickname" => "无尽猴子五号机",  
                            "Type" => "0");
        $database->insertSingleArray1($tableName, $valueArray);
        echo $database->getQueryString();
        echo "<br/>";
        
        echo "Insert multiple data : <br/>";
        $valueArray = array(array(  "Name" => "monkey009", 
                                    "Password" => "monkey", 
                                    "Nickname" => "无尽猴子九号机",  
                                    "Type" => "0"), 
                            array(  "Name" => "monkey010", 
                                    "Password" => "monkey", 
                                    "Nickname" => "无尽猴子十号机",  
                                    "Type" => "0"), 
                            array(  "Name" => "monkey011", 
                                    "Password" => "monkey", 
                                    "Nickname" => "无尽猴子十一号机",  
                                    "Type" => "0"));
        $database->insertMultipleArray1($tableName, $valueArray);
        echo $database->getQueryString();
        echo "<br/>";
        echo "<hr/>";
    }
    
    createTest();
    insertTest();
?>
