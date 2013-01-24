<?php
    include_once "account_regex.php";
    include_once $_SERVER['DOCUMENT_ROOT'].'/api/data/sql_photo.php';

    /**
     * The APIs about album.
     * @author ZHG <CyberZHG@gmail.com>
     */
    class Account_Photo
    {
        public static function getPhotos($albumID)
        {
            $sql_photo = new SQL_Photo();
            return $sql_photo->select($albumID);
        }
        
        public static function getPhotosNumber($albumID)
        {
            return count(Account_Photo::getPhotos($albumID));
        }
        
        public static function getMaximumIndice($albumID)
        {
            $sql_photo = new SQL_Photo();
            $result = $sql_photo->select($albumID);
            foreach($result as $row)
            {
                return $row["Indice"];
            }
            return 0;
        }
    }
?>
