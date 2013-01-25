<?php
    include_once $_SERVER["DOCUMENT_ROOT"] . '/api/data/sql_application.php';
    include_once $_SERVER["DOCUMENT_ROOT"] . '/api/data/sql_application_permission.php';
    
    /**
     * The basic application operaions.
     * @author ZHG <CyberZHG@gmail.com>
     */
    class Application_Application 
    {
        /**
         * Get all applications of the user.
         * @param integer $userID The id of the user.
         * @return array Query result.
         */
        public static function getUserApplications($userID)
        {
            $sql_application = new SQL_Application();
            return $sql_application->selectByUser($userID);
        }
        
        /**
         * Get the basic information of the user.
         * @param integer $applicationID The id of the application.
         * @return array Query result.
         */
        public static function getApplicationInformation($applicationID)
        {
            $sql_application = new SQL_Application($applicationID);
            return $sql_application->select($applicationID);
        }
        
        /**
         * Get the permission status of the application.
         * @param integer $applicationID The id of the application.
         * @return array Query result.
         */
        public static function getApplicationPermissions($applicationID)
        {
            $sql_application_permission = new SQL_Application_Permission();
            return $sql_application_permission->selectByApplication($applicationID);
        }
    }
?>
