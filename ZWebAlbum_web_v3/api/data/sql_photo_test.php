<!DOCTYPE html>

<html>
    <head>
        <meta charset = "utf-8">
        <title>SQL_Photo_Test</title>
    </head>
    
    <body>
        <?php
            /**
             * The test of sql_photo_test.php.
             * @author ZHG
             * @version 20130115
             */
            include_once "sql_photo.php";
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
                $sql_photo = new SQL_Photo();
                $sql_photo->createTable();
                printQueryResult($sql_photo->selectWithLimit());
                echo "<hr/>";
            }

            /**
             * SELECT Test.
             */
            function selectTest()
            {
                echo "Select Test <hr/>";
                $sql_photo = new SQL_Photo();
                printQueryResult($sql_photo->select(2));
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
                $sql_photo = new SQL_Photo();
                $photo = array
                (
                    "AlbumID" => "2",
                    "Description" => "猴子的一号测试照片",
                    "PhotoPath" => "pages"
                );
                $sql_photo->insert($photo);
                echo mysql_error();
                $id = $sql_photo->getAutoIncrementID();
                printQueryResult($sql_photo->selectWithLimit());
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
                $sql_photo = new SQL_Photo();
                $user = array
                (
                    "PhotoPath" => ""
                );
                $sql_photo->update($id, $user);
                printQueryResult($sql_photo->selectWithLimit());
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
                $sql_photo = new SQL_Photo();
                $sql_photo->delete($id);
                printQueryResult($sql_photo->selectWithLimit());
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
