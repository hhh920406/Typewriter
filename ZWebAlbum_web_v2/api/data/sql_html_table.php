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
     * @var string $tableStyle The CSS style of table.
     * @var string $headStyle The CSS style of table head.
     * @var string $rowStyle1 The CSS style 1 of table row.
     * @var string $rowStyle2 The CSS style 2 of table row.
     * @var string $buttonStyle The CSS style of input button.
     * @var string $buttonStyle The CSS style of input text.
     */
    private $sql_table = "";
    private $tableStyle = "
        text-align: center;
        width: 100%; 
        margin: 0 auto; 
        border: 1;";
    private $headStyle = "
        font-weight: bold; 
        background-color: black; 
        color: white;";
    private $rowStyle1 = "
        height: 60px;
        background-color: #404040;
        color: white;";
    private $rowStyle2 = "
        height: 60px;
        background-color: #303030;
        color: white;";
    private $insertStyle = "
        height: 30px;
        background-color: #DDDDDD;";
    private $buttonStyle = "
        width: 80px;
        height: 30px;";
    private $inputStyle = "
        width: 80%;
        height: 30px;";
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
     * Set the CSS Style of the SQL_Table.
     * @param string $tableStyle The style of table.
     * @param string $headStyle The style of table head.
     * @param string $rowStyle1 One style of table row.
     * @param string $rowStyle2 The other style of table row.
     * @param string $insertStyle The style of insert row.
     * @param string $buttonStyle The style of button input.
     * @param string $inputStyle The style of text input.
     */
    public function setStyle($tableStyle, $headStyle, $rowStyle1, $rowStyle2, $insertStyle, $buttonStyle, $inputStyle)
    {
        $this->tableStyle = $tableStyle;
        $this->headStyle = $headStyle;
        $this->rowStyle1 = $rowStyle1;
        $this->rowStyle2 = $rowStyle2;
        $this->insertStyle = $insertStyle;
        $this->buttonStyle = $buttonStyle;
        $this->inputStyle = $inputStyle;
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
        $html .= "<input type='button' value='Update' style='" . $this->buttonStyle . "'>";
        $html .= "</input>";
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
        $html .= "<input type='button' value='Delete' style='" . $this->buttonStyle . "'>";
        $html .= "</input>";
        return $html;
    }
    
    /**
     * Generate the HTML of the insert button.
     * @return string The HTML code. 
     */
    public function generateInsertButton()
    {
        $html = "";
        $html .= "<input type='button' value='Insert' style='" . $this->buttonStyle . "'>";
        $html .= "</input>";
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
            $html .= "<tr style='" . $this->headStyle . "'>";
            foreach($row as $key => $value)
            {
                if(is_string($key))
                {
                    $html .= "<td>" . htmlEntities($key, ENT_QUOTES, "UTF-8") . "</td>";
                }
            }
            if($this->showUpdate || $this->showDelete)
            {
                $html .= "<td>Operate</td>";
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
        $style = 1;
        foreach($result as $row)
        {
            if($style == 1)
            {
                $html .= "<tr style='" . $this->rowStyle1 . "'>";
                $style = 2;
            }
            else
            {
                $html .= "<tr style='" . $this->rowStyle2 . "'>";
                $style = 1;
            }
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
        $html .= "<tr style='" . $this->rowStyle2 . "'>";
        foreach($result as $row)
        {
            foreach($row as $key => $value)
            {
                if(is_string($key))
                {
                    $html .= "<td>";
                    $html .= "<input type='text' style='" . $this->inputStyle . "'>";
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
            $html .= "<table style='" . $this->tableStyle . "'>";
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
