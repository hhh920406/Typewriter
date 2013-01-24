<!DOCTYPE html>

<html>
    <head>
        <meta charset = "utf-8">
        <title>SQL_Album_Test</title>
    </head>
    
    <body>
        <?php
            /**
             * The test of sql_album_test.php.
             * @author ZHG
             * @version 20130115
             */
            include_once "sql_album.php";
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
                $sql_album = new SQL_Album();
                $sql_album->createTable();
                printQueryResult($sql_album->selectWithLimit());
                echo "<hr/>";
            }

            /**
             * SELECT Test.
             */
            function selectTest()
            {
                echo "Select Test <hr/>";
                $sql_album = new SQL_Album();
                printQueryResult($sql_album->select(1));
                printQueryResult($sql_album->selectByUser(3));
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
                $sql_album = new SQL_Album();
                $user = array
                (
                    "UserID" => "1",
                    "Name" => "一号测试相册",
                    "Description" => "猴子的一号测试相册"
                );
                $sql_album->insert($user);
                $id = $sql_album->getAutoIncrementID();
                printQueryResult($sql_album->selectWithLimit());
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
                $sql_album = new SQL_Album();
                $user = array
                (
                    "Name" => "一号测试相册",
                    "Description" => "被修改的猴子的一号测试相册"
                );
                $sql_album->update($id, $user);
                printQueryResult($sql_album->selectWithLimit());
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
                $sql_album = new SQL_Album();
                $sql_album->delete($id);
                printQueryResult($sql_album->selectWithLimit());
                echo "<hr/>";
            }

            createTest();
            selectTest();
            insertTest();
            updateTest();
            deleteTest();
        ?>
    </body>
</html>
