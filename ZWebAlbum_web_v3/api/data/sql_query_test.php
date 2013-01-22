<?php
/**
 * The test of the sqlQuery.php.
 * @author ZHG
 * @version 20130115
 */
include_once "sql_query.php";
include_once "sql_define.php";

/**
 * @var string $databaseName The sql_query used for testing.
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
    $sql_query = new SQL_Query("", "", "", $databaseName);
    echo "<hr/>";

    echo "Create sql_query: <br/>";
    $sql_query->createDatabase($databaseName);
    echo $sql_query->getQueryString();
    echo "<br/>";

    echo "Create table: <br/>";
    $typeArray = array( "ID" => "INT(4) NOT NULL AUTO_INCREMENT",
                        "Name" => "VARCHAR(45) NOT NULL UNIQUE",
                        "Password" => "VARCHAR(45) NOT NULL",
                        "Nickname" => "VARCHAR(45) DEFAULT ''",
                        "Type" => "INT(4) DEFAULT '0'");
    $primaryArray = array("ID");
    $sql_query->createTable($tableName, $typeArray, $primaryArray);
    echo $sql_query->getQueryString();
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
    $sql_query = new SQL_Query("", "", "", $databaseName);
    echo "<hr/>";
    echo "Insert multiple: <br/>";
    $columnArray = array("Name", "Password", "Nickname", "Type");
    $valueArray = array(array("monkey015", "monkey", "无尽猴子十五号机", "0"),
                        array("monkey016", "monkey", "无尽猴子十六号机", "0"),
                        array("monkey017", "monkey", "无尽猴子十七号机", "0"));
    $sql_query->insert($tableName, $columnArray, $valueArray);
    echo $sql_query->getQueryString();
    echo "<br/>";
    echo "Insert single: <br/>";
    $valueArray = array("monkey018", "monkey", "无尽猴子十八号机", "0");
    $sql_query->insert($tableName, $columnArray, $valueArray);
    echo $sql_query->getQueryString();
    echo "<br/>";
    echo mysql_error();
    echo "<hr/>";
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
    $sql_query = new SQL_Query("", "", "", $databaseName);
    echo "<hr/>";
    $columnNames = array();
    $condition = array( "Password = 'monkey'",
                        "Nickname = '无尽猴子十二号机'");
    $relation = "OR";
    $order = "ID DESC";
    $limit = array(0, 1);
    $sql_query->select($tableName, $columnNames, $condition, $relation, $order, $limit);
    echo $sql_query->getQueryString();
    printQueryResult($sql_query->getAllResult());
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
    $sql_query = new SQL_Query("", "", "", $databaseName);
    echo "<hr/>";
    $updateValue = array("Nickname" => "无尽猴子更新测试");
    $condition = "ID = 1";
    $sql_query->update($tableName, $updateValue, $condition);
    echo $sql_query->getQueryString();
    $sql_query->select($tableName, "", $condition);
    printQueryResult($sql_query->getAllResult());
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
    $sql_query = new SQL_Query("", "", "", $databaseName);
    echo "<hr/>";
    $condition = "Nickname = '无尽猴子十六号机'";
    $sql_query->delete($tableName, $condition);
    echo $sql_query->getQueryString();
    $sql_query->select($tableName, "", $condition);
    printQueryResult($sql_query->getAllResult());
    echo "<hr/>";
}

createTest();
insertTest();
selectTest();
updateTest();
deleteTest();
?>
