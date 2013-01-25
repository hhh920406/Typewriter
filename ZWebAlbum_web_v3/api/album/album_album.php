<?php
    include_once $_SERVER['DOCUMENT_ROOT'].'/api/data/sql_album.php';

    /**
     * The APIs about album.
     * @author ZHG <CyberZHG@gmail.com>
     */
    class Album_Album
    {
        public static function getAllAlbums($userID)
        {
            $sql_album = new SQL_Album();
            return $sql_album->selectByUser($userID);
        }
        
        public static function getAlbumsNumber($userID)
        {
            return count(Album_Album::getAlbumsNumber($userID));
        }
        
        public static function getMaximumIndice($userID)
        {
            $sql_album = new SQL_Album();
            $result = $sql_album->selectByUser($userID);
            foreach($result as $row)
            {
                return $row["Indice"];
            }
            return 0;
        }
    }
?>
