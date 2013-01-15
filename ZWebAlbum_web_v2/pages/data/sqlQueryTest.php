<?php
/**
 * The test of the sqlQuery.php.
 * @author ZHG
 * @version 20130115
 */
include "sqlQuery.php";

/**
 * @var string $databaseName The database used for testing.
 * @var string $tableName The table used for testing.
 */
$databaseName = "Test";
$tableName = "User_Test";

/**
 * Test CREATE operation.
 * @global string $databaseName
 * @global string $tableName
 */
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
                        "Name" => "VARCHAR(45) NOT NULL UNIQUE",
                        "Password" => "VARCHAR(45) NOT NULL",
                        "Nickname" => "VARCHAR(45) DEFAULT ''",
                        "Type" => "INT(4) DEFAULT '0'");
    $primaryArray = array("ID");
    $database->createTable($tableName, $typeArray, $primaryArray);
    echo $database->getQueryString();
    echo "<br/>";
    echo "<hr/>";
}

/**
 * Test INSERT operation.
 * @global string $databaseName
 * @global string $tableName
 */
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

/**
 * Print the query result.
 * @param array $result The result array.
 */
function printQueryResult($result)
{
    echo "<br/>";
    echo "<table border='1'>";
    if($result)
    {
        for($i = 0; $i < count($result); ++ $i)
        {
            if(0 == $i)
            {
                echo "<tr>";
                foreach($result[$i] as $column => $value)
                {
                    if(is_integer($column))
                    {
                        continue;
                    }
                    echo "<th>" . $column . "</th>";
                }
                echo "</tr>";
            }
            echo "<tr>";
            foreach($result[$i] as $column => $value)
            {
                if(is_integer($column))
                {
                    continue;
                }
                echo "<td>" . $value . "</td>";
            }
            echo "</tr>";
        }
    }
    else
    {
        echo "<tr><th>NULL</th></tr>";
    }
    echo "</table>";
    echo "<br/>";
}

/**
 * Test SELECT operation.
 * @global string $databaseName
 * @global string $tableName
 */
function selectTest()
{
    global $databaseName;
    global $tableName;
    echo "SELECT Test";
    $database = new Database("", "", "", $databaseName);
    echo "<hr/>";
    $columnNames = array();
    $condition = array( "Password = 'monkey'",
                        "Nickname = '无尽猴子十二号机'");
    $relation = "OR";
    $order = "ID DESC";
    $limit = array(0, 1);
    $database->select($tableName, $columnNames, $condition, $relation, $order, $limit);
    echo $database->getQueryString();
    printQueryResult($database->getAllResult());
    echo "<hr/>";
}

/**
 * Test UPDATE operation.
 * @global string $databaseName
 * @global string $tableName
 */
function updateTest()
{
    global $databaseName;
    global $tableName;
    echo "UPDATE Test";
    $database = new Database("", "", "", $databaseName);
    echo "<hr/>";
    $updateValue = array("Nickname" => "无尽猴子更新测试");
    $condition = "ID = 1";
    $database->update($tableName, $updateValue, $condition);
    echo $database->getQueryString();
    $database->select($tableName, "", $condition);
    printQueryResult($database->getAllResult());
    echo "<hr/>";
}

/**
 * Test DELETE operation.
 * @global string $databaseName
 * @global string $tableName
 */
function deleteTest()
{
    global $databaseName;
    global $tableName;
    echo "DELETE Test";
    $database = new Database("", "", "", $databaseName);
    echo "<hr/>";
    $condition = "Nickname = '无尽猴子十六号机'";
    $database->delete($tableName, $condition);
    echo $database->getQueryString();
    $database->select($tableName, "", $condition);
    printQueryResult($database->getAllResult());
    echo "<hr/>";
}

createTest();
insertTest();
selectTest();
updateTest();
deleteTest();
?>
