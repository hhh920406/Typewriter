<?php
    include_once $_SERVER["DOCUMENT_ROOT"] . "/api/data/sql_album.php";

    /**
     * The APIs about album.
     * @author ZHG <CyberZHG@gmail.com>
     */
    class Album_Album
    {
        /**
         * Get all albums from the user.
         * @param int $userID
         * @return array Query result.
         */
        public static function getAlbums($userID, $start = 0, $number = 0)
        {
            $sql_album = new SQL_Album();
            return $sql_album->selectByUser($userID, $start, $number);
        }

        /**
         * Get the number of albums belong to the user.
         * @param int $userID albumID
         * @return int Album number.
         */
        public static function getAlbumNumber($userID)
        {
            $sql_album = new SQL_Album();
            return $sql_album->getNumberByUser($userID);
        }

        /**
         * Get the largest indice for sorting.
         * @param int $userID
         * @return int The largest indice plus one.
         */
        private static function getNextIndice($userID)
        {
            $sql_album = new SQL_Album();
            $result = $sql_album->selectByUser($userID, 0, 1);
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
            $albumInfo["Indice"] = Album_Album::getNextIndice($albumInfo["UserID"]);
            return $sql_album->insert($albumInfo);
        }

        public static function delete($albumID)
        {
            $sql_album = new SQL_Album();
            return $sql_album->delete($albumID);
        }
    }
?>
