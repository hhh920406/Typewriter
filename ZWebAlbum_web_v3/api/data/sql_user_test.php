<?php
/**
 * The test of sql_user_test.php.
 * @author ZHG
 * @version 20130115
 */
include_once "sql_user.php";
include_once "sql_define.php";

/**
 * @var int $id The id for testing.
 */
$id = 0;

/**
 * CREATE Test.
 */
function createTest()
{
    echo "Create Table Test <hr/>";
    $sql_user = new SQL_User();
    $sql_user->createTable();
    printQueryResult($sql_user->selectWithLimit());
    echo "<hr/>";
}

/**
 * SELECT Test.
 */
function selectTest()
{
    echo "Select Test <hr/>";
    $sql_user = new SQL_User();
    printQueryResult($sql_user->select(1));
    printQueryResult($sql_user->selectByName("MonkeyAdmin"));
    printQueryResult($sql_user->selectByPassword("MonkeyAdmin", "monkey"));
    echo "<hr/>";
}

/**
 * INSERT Test.
 * @global int $id
 */
function insertTest()
{
    global $id;
    echo "Insert Test <hr/>";
    $sql_user = new SQL_User();
    $user = array
    (
        "Name" => "monkey019",
        "Password" => "monkey",
        "Nickname" => "无限猴子十九号机"
    );
    $sql_user->insert($user);
    $id = $sql_user->getAutoIncrementID();
    printQueryResult($sql_user->selectWithLimit());
    echo "Auto Increment ID: " . $id;
    echo "<hr/>";
}

/**
 * UPDATE test.
 * @global int $id
 */
function updateTest()
{
    global $id;
    echo "Update Test <hr/>";
    $sql_user = new SQL_User();
    $user = array
    (
        "Name" => "monkey019",
        "Password" => "monkey",
        "Nickname" => "被修改的猴子"
    );
    $sql_user->update($id, $user);
    printQueryResult($sql_user->selectWithLimit());
    echo "<hr/>";
}

/**
 *DELETE Test.
 * @global int $id
 */
function deleteTest()
{
    global $id;
    echo "Delete Test <hr/>";
    $sql_user = new SQL_User();
    $sql_user->delete($id);
    printQueryResult($sql_user->selectWithLimit());
    echo "<hr/>";
}

createTest();
selectTest();
insertTest();
updateTest();
deleteTest();
?>
