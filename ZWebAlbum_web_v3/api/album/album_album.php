<?php
    include_once $_SERVER["DOCUMENT_ROOT"] . "/api/data/sql_album.php";

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

        public static function getAlbumByName($userID, $name)
        {
            $sql_album = new SQL_Album();
            return $sql_album->selectByName($userID, $name);
        }
        
        public static function getAlbumsNumber($userID)
        {
            return count(Album_Album::getAlbumsNumber($userID));
        }
        
        public static function getNextIndice($userID)
        {
            $sql_album = new SQL_Album();
            $result = $sql_album->selectByUser($userID);
            foreach($result as $row)
            {
                return $row["Indice"] + 1;
            }
            return 1;
        }

        public static function select($albumID)
        {
            $sql_album = new SQL_Album();
            return $sql_album->select($albumID);
        }

        public static function update($albumID, $albumInfo)
        {
            $sql_album = new SQL_Album();
            return $sql_album->update($albumID, $albumInfo);
        }

        public static function insert($albumInfo)
        {
            $sql_album = new SQL_Album();
            $albumInfo["Indice"] = getNextIndice($albumInfo["UserID"]);
            return $sql_album->insert($albumInfo);
        }

        public static function delete($albumID)
        {
            $sql_album = new SQL_Album();
            return $sql_album->delete($albumID);
        }

        public function getAutoIncrementID()
        {
            $sql_album = new SQL_Album();
            return $sql_album->getAutoIncrementID();
        }
    }
?>
