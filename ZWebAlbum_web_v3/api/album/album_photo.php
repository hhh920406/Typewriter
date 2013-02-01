<?php
    include_once $_SERVER["DOCUMENT_ROOT"] . "/api/data/sql_photo.php";

    /**
     * The APIs about album.
     * @author ZHG <CyberZHG@gmail.com>
     */
    class Album_Photo
    {
        /**
         * Get all the photos in the album.
         * @param int $albumID
         * @return array Query result.
         */
        public static function getPhotos($albumID, $start = 0, $number = 0)
        {
            $sql_photo = new SQL_Photo();
            return $sql_photo->selectByAlbum($albumID, $start, $number);
        }

        /**
         * Get the number of photos in the album.
         * @param int $albumID
         * @return array Query result.
         */
        public static function getPhotoNumber($albumID)
        {
            $sql_photo = new SQL_Photo();
            return $sql_photo->getNumberByAlbum($albumID);
        }

        /**
         * Get the largest indice of the album.
         * @param int $albumID
         * @return int The largest indice plus one.
         */
        private static function getNextIndice($albumID)
        {
            $sql_photo = new SQL_Photo();
            $result = $sql_photo->selectByAlbum($albumID, 0, 1);
            foreach($result as $row)
            {
                return $row["Indice"] + 1;
            }
            return 1;
        }

        /**
         * Delete all the photos in the album.
         * @param int $albumID
         */
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
            $photoInfo["Indice"] = Album_Photo::getNextIndice($photoInfo["AlbumID"]);
            return $sql_photo->insert($photoInfo);
        }

        public static function delete($photoID)
        {
            $sql_photo = new SQL_Photo();
            return $sql_photo->delete($photoID);
        }
    }
?>
