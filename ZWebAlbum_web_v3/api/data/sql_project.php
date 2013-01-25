<?php
include_once "sql_define.php";
include_once "sql_query.php";
include_once "sql_user.php";
include_once "sql_album.php";
include_once "sql_photo.php";
include_once "sql_application.php";
include_once "sql_application_permission.php";
include_once "sql_user_application.php";

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
        unset($sql_user);
        $sql_album = new SQL_Album();
        $sql_album->createTable();
        unset($sql_album);
        $sql_photo = new SQL_Photo();
        $sql_photo->createTable();
        unset($sql_photo);
        $sql_application = new SQL_Application();
        $sql_application->createTable();
        unset($sql_application);
        $sql_application_permission = new SQL_Application_Permission();
        $sql_application_permission->createTable();
        unset($sql_application_permission);
        $sql_user_application = new SQL_User_Application();
        $sql_user_application->createTable();
        unset($sql_user_application);
    }
}
?>
