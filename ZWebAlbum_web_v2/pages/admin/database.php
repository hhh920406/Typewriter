<!DOCTYPE html>

<html>
    <head>
        <meta charset="utf-8">
        <title>数据库操作</title>
        <link rel="stylesheet" href="/css/main/common.css">
        <link rel="stylesheet" href="/css/main/master.css">
		<link rel="stylesheet" href="/css/admin/database.css"> 
    </head>
    <body>
        <?php include $_SERVER['DOCUMENT_ROOT'].'/pages/main/header.php';?>
        <div id="pageBody">
            <div id="sql_table">
                <?php
                    include_once "sql_table.php";
                    /**
                     * Generate HTML table to operate database.
                     * @authore ZHG
                     */
                    class SQL_HTML_Table
                    {
                        /**
                         * @var SQL_HTML_Table $sql_table The connector to MySQL server.
                         */
                        private $sql_table = "";
                        /**
                         * @var integer $showInsert The value is 1 if the table contains a row to insert, else is 0.
                         * @var integer $showUpdate The value is 1 if the table row contains a button to update, else is 0.
                         * @var integer $showDelete The value is 1 if the table row contains a button to delete, else is 0.
                         */
                        private $showInsert = 1;
                        private $showUpdate = 1;
                        private $showDelete = 1;
                        /**
                         * @var integer $itemsPerPage The items shown per page.
                         * @var string $primaryKey The primary key of the table.
                         */
                        private $itemsPerPage = 30;
                        private $primaryKey = "";
                        
                        /**
                         * Get SQL_Table, the connector of MySQL server.
                         * @param SQL_Table $sql_table The implement of SQL_Table.
                         */
                        public function __construct($sql_table, $primaryKey)
                        {
                            $this->sql_table = $sql_table;
                            $this->primaryKey = $primaryKey;
                        }
                        
                        /**
                         * Set the functions of the table.
                         * @param integer $showInsert If it is available to insert to the table.
                         * @param integer $showUpdate If it is available to update the table row. 
                         * @param integer $showDelete If it is available to delete the table row.
                         */
                        public function setEditable($showInsert, $showUpdate, $showDelete)
                        {
                            $this->showInsert = $showInsert;
                            $this->showUpdate = $showUpdate;
                            $this->showDelete = $showDelete;
                        }
                        
                        /**
                         * Set the items number shown per page.
                         * @param integer $itemsPerPage The item number.
                         */
                        public function setItemsPerPage($itemsPerPage)
                        {
                            $this->itemsPerPage = $itemsPerPage;
                        }
                        
                        /**
                         * Generate the HTML of the update button.
                         * @param array $key The primary key value.
                         * @return string The HTML code. 
                         */
                        private function generateUpdateButton($key)
                        {
                            $html = "";
                            $html .= "<a href='sql_html_table_update.php'>";
                            $html .= "<img width='16' height='16' alt='Update' title='Update' src='/resource/images/icon_update.png'>";
                            $html .= "</img>";
                            $html .= "Update";
                            $html .= "</a>";
                            return $html;
                        }
                        
                        /**
                         * Generate the HTML of the delete button.
                         * @param array $key The primary key value.
                         * @return string The HTML code. 
                         */
                        private function generateDeleteButton($key)
                        {
                            $html = "";
                            $html .= "<a href='sql_html_table_delete.php'>";
                            $html .= "<img width='16' height='16' alt='Delete' title='Delete' src='/resource/images/icon_delete.png'>";
                            $html .= "</img>";
                            $html .= "Delete";
                            $html .= "</a>";
                            return $html;
                        }
                        
                        /**
                         * Generate the HTML of the insert button.
                         * @return string The HTML code. 
                         */
                        public function generateInsertButton()
                        {
                            $html = "";
                            $html .= "<a href='sql_html_table_insert.php'>";
                            $html .= "<img width='16' height='16' alt='Insert' title='Insert' src='/resource/images/icon_insert.png'>";
                            $html .= "</img>";
                            $html .= "Insert";
                            $html .= "</a>";
                            return $html;
                        }
                        
                        /**
                         * Generate the HTML of table head.
                         * @param array $result The query result.
                         * @return string The HTML code. 
                         */
                        private function generateHead($result)
                        {
                            $html = "";
                            foreach($result as $row)
                            {
                                $html .= "<tr>";
                                foreach($row as $key => $value)
                                {
                                    if(is_string($key))
                                    {
                                        $html .= "<th>" . htmlEntities($key, ENT_QUOTES, "UTF-8") . "</th>";
                                    }
                                }
                                if($this->showUpdate || $this->showDelete)
                                {
                                    $html .= "<th style='width: 200px;'>Operate</th>";
                                }
                                $html .= "</tr>";
                                break;
                            }
                            return $html;
                        }
                        
                        /**
                         * Generate the HTML of table row.
                         * @param array $result The query result.
                         * @return string The HTML code. 
                         */
                        private function generateRow($result)
                        {
                            $html = "";
                            foreach($result as $row)
                            {
                                $html .= "<tr>";
                                foreach($row as $key => $value)
                                {
                                    if(is_string($key))
                                    {
                                        $html .= "<td>" . htmlEntities($value, ENT_QUOTES, "UTF-8") . "</td>";
                                    }
                                }
                                if($this->showUpdate || $this->showDelete)
                                {
                                    $html .= "<td>";
                                    if($this->showUpdate)
                                    {
                                        $html .= $this->generateUpdateButton($row[$this->primaryKey]);
                                    }
                                    if($this->showDelete)
                                    {
                                        $html .= $this->generateDeleteButton($row[$this->primaryKey]);
                                    }
                                    $html .= "</td>";
                                }
                                $html .= "</tr>";
                            }
                            return $html;
                        }
                        
                        /**
                         * Generate the HTML of insertion row.
                         * @param array $result The query result.
                         * @return string The HTML code. 
                         */
                        public function generateInsertRow($result)
                        {
                            $html = "";
                            $html .= "<tr>";
                            foreach($result as $row)
                            {
                                foreach($row as $key => $value)
                                {
                                    if(is_string($key))
                                    {
                                        $html .= "<td>";
                                        $html .= "<input type='text'>";
                                        $html .= "</input>";
                                        $html .= "</td>";
                                    }
                                }
                                break;
                            }
                            $html .= "<td>";
                            $html .= $this->generateInsertButton();
                            $html .= "</td>";
                            $html .= "</tr>";
                            return $html;
                        }
                        
                        /**
                         * Generate a HTML table with the given page number.
                         * @param integer $pageNumber The page number.
                         * @return The HTML table.
                         */
                        public function generateHTMLTable($pageNumber)
                        {
                            $html = "";
                            $operate = $this->showUpdate || $this->showDelete;
                            $result = $this->sql_table->selectWithPage($this->itemsPerPage, $pageNumber);
                            if($result)
                            {
                                $html .= "<table>";
                                $html .= $this->generateHead($result);
                                $html .= $this->generateRow($result);
                                if($this->showInsert)
                                {
                                    $html .= $this->generateInsertRow($result);
                                }
                                $html .= $this->generateHead($result);
                                $html .= "</table>";
                            }
                            return $html;
                        }
                    }
                ?>
            </div>
        </div>
        <?php include $_SERVER['DOCUMENT_ROOT'].'/pages/main/footer.php';?>
    </body>
</html>
