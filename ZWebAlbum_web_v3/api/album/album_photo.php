<?php
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
        
        public static function getNextIndice($albumID)
        {
            $sql_photo = new SQL_Photo();
            $result = $sql_photo->select($albumID);
            foreach($result as $row)
            {
                return $row["Indice"] + 1;
            }
            return 1;
        }

        public static function deleteAllPhotos($albumID)
        {
            $sql_photo = new SQL_Photo();
            return $sql_photo->deleteByAlbum($albumID);
        }

        public static function select($photoID)
        {
            $sql_photo = new SQL_Photo();
            return $sql_photo->select($photoID);
        }

        public static function update($photoID, $photoInfo)
        {
            $sql_photo = new SQL_Photo();
            return $sql_photo->update($photoID, $photoInfo);
        }

        public static function insert($photoInfo)
        {
            $sql_photo = new SQL_Photo();
            $photoInfo["Indice"] = getNextIndice($photoInfo["AlbumID"]);
            return $sql_photo->insert($photoInfo);
        }

        public static function delete($photoID)
        {
            $sql_photo = new SQL_Photo();
            return $sql_photo->delete($photoID);
        }

        public function getAutoIncrementID()
        {
            $sql_album = new SQL_Album();
            return $sql_album->getAutoIncrementID();
        }
    }
?>
