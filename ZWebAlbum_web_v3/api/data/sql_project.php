<?php
include_once "sql_define.php";
include_once "sql_query.php";
include_once "sql_user.php";
include_once "sql_album.php";
include_once "sql_photo.php";

/**
 * Provide operations for the project database.
 * @author ZHG
 * @version 20130115
 */
class SQL_Project
{
    /**
     * Create the project database.
     */
    public function createProjectDatabase()
    {
        $sql_query = new SQL_Query();
        $sql_query->createDatabase(DATABASE);
        $sql_user = new SQL_User();
        $sql_user->createTable();
        $sql_album = new SQL_Album();
        $sql_album->createTable();
        $sql_photo = new SQL_Photo();
        $sql_photo->createTable();
    }
}
?>
