<?php
    include_once "sql_define.php";
    include_once "sql_table.php";
    include_once "sql_query.php";

    /**
     * The SQL operation for photo table.
     * @author ZHG
     */
    class SQL_Photo extends SQL_Table
    {
        /**
         * Change the table name.
         */
        public function __construct()
        {
            parent::__construct();
            $this->tableName = "D_Photo";
            $this->primaryKeyName = "PhotoID";
        }

        /**
         * Create the album table.
         */
        public function createTable()
        {
            $columns = array
            (
                $this->primaryKeyName   =>  "INT(4) NOT NULL AUTO_INCREMENT " . 
                                            "COMMENT 'The ID of photo. '",
                "AlbumID"               =>  "INT(4) NOT NULL " . 
                                            "COMMENT 'The ID of the album who contains the photo. '",
                "Description"           =>  "VARCHAR(200) DEFAULT '' " . 
                                            "COMMENT 'The Description of the photo. '",
                "PhotoPath"             =>  "TEXT " . 
                                            "COMMENT 'The saved path of the photo. '",
                "Indice"                =>  "INT(4) DEFAULT '0' " . 
                                            "COMMENT 'The value used to sort. '"
            );
            $primary = $this->primaryKeyName;
            $this->sql_query->createTable($this->tableName, $columns, $primary);
            $this->sql_query->alterForeignKey($this->tableName, "AlbumID", "D_Album", "AlbumID");
        }

        /**
         * Select by album.
         * @param integer $albumID
         * @return array Query result.
         */
        public function selectByAlbum($albumID, $start = 0, $number = 0)
        {
            $condition = $this->getEqualCondition(array(
                "AlbumID" => $albumID
            ));
            if($start || $number)
            {
                $limit = array($start, $number);
                $this->sql_query->select($this->tableName, "", $condition, "", "Indice DESC", $limit);
            }
            else
            {
                $this->sql_query->select($this->tableName, "", $condition, "", "Indice DESC");
            }
            return $this->sql_query->getAllResult();
        }

        /**
         * Delete all photos in the album.
         * @param int $albumID
         * @return boolean
         */
        public function deleteByAlbum($albumID)
        {
            $condition = $this->getEqualCondition(array(
                "AlbumID" => $albumID
            ));
            $this->sql_query->delete($this->tableName, $condition);
            if(mysql_error())
            {
                return false;
            }
            return true;
        }

        /**
         * Get the number of photos in the album.
         * @param int $albumID
         * @return int Photo number.
         */
        public function getNumberByAlbum($albumID)
        {
            $condition = $this->getEqualCondition(array(
                "AlbumID" => $albumID
            ));
            $this->sql_query->count($this->tableName, $condition);
            $result = $this->sql_query->getSingleResult();
            return $result[0];
        }
    }
?>
