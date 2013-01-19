<?php
include_once "sql_user.php";
include_once "sql_html_table.php";
/**
 * The test for SQL_HTML_Table class.
 * @author ZHG
 */
echo "<h2>" . "SQL_HTML_Table Test" . "</h2>";
echo "<hr/>";
$sql_user = new SQL_User();
$sql_html_table = new SQL_HTML_Table($sql_user);
$html = $sql_html_table->generateHTMLTable(1);
echo $html;
echo "<hr/>";
print htmlSpecialChars($html);
?>
