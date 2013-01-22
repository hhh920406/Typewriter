<?php

define("HOST", "localhost");
define("NAME", "ZHG");
define("PASSWORD", "19910702");
define("DATABASE", "ZWebAlbum_v2");


/**
 * Print the query result.
 * @param array $result The result array.
 */
function printQueryResult($result)
{
    echo "<br/>";
    echo "<table border='1'>";
    if($result)
    {
        for($i = 0; $i < count($result); ++ $i)
        {
            if(0 == $i)
            {
                echo "<tr>";
                foreach($result[$i] as $column => $value)
                {
                    if(is_integer($column))
                    {
                        continue;
                    }
                    echo "<th>" . $column . "</th>";
                }
                echo "</tr>";
            }
            echo "<tr>";
            foreach($result[$i] as $column => $value)
            {
                if(is_integer($column))
                {
                    continue;
                }
                echo "<td>" . $value . "</td>";
            }
            echo "</tr>";
        }
    }
    else
    {
        echo "<tr><th>NULL</th></tr>";
    }
    echo "</table>";
    echo "<br/>";
}
?>
