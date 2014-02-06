<?php
/**
 * 测试常用函数。
 * @author ZHG <CyberZHG@gmail.com>
 */

/**
 * 以表格的形式输出stdClass数组。
 * @param array $array 要输出的数组。
 */
function printArrayWithTable($array) {
    echo "<table border = 1>";
    for ($i = 0; $i < count($array); ++ $i) {
        $item = $array[$i];
        if (0 === $i) {
            echo "<tr>";
            foreach ($item as $key => $value) {
                if (is_string($key)) {
                    echo "<th>";
                    echo $key;
                    echo "</th>";
                }
            }
            echo "</tr>";
        }
        echo "<tr>";
        foreach($item as $key => $value) {
            if (is_string($key)) {
                echo "<td>";
                if ("sellerLogo" === $key || "itemImage" === $key) {
                    echo "<img src = '";
                    echo $value;
                    echo "'></img>";
                } else if (strpos($key, "Url") !== false) {
                    echo "<a href = '";
                    echo $value;
                    echo "'>";
                    echo $value;
                    echo "</a>";
                } else if (is_bool($value)) {
                    if ($value) {
                        echo "是";
                    } else {
                        echo "否";
                    }
                } else {
                    echo $value;
                }
                echo "</td>";
            }
        }
        echo "</tr>";
    }
    echo "</table>";
}
?>
