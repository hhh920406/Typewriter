<?php
$categoryDir = "D:/Apache2.2/htdocs/ZShopping_web/data/category";
$dir = opendir($categoryDir);
$writeFile = fopen("category.tree", "w");
if ($dir && $writeFile) {
    while ($file = readdir($dir)) {
        $categoryID = "";
        for ($i = 9; $i < strlen($file); ++$i) {
            $categoryID .= $file[$i];
        }
        $categoryFile = fopen($categoryDir . "/" . $file, "r");
        if ($categoryFile) {
            $items = "";
            while (!feof($categoryFile)) {
                $items .= fread($categoryFile, 1024);
            }
            fclose($categoryFile);
            $items = json_decode($items);
            $info = $categoryID . " " . count($items);
            for ($i = 0; $i < count($items); ++$i) {
                $info .= " " . $items[$i]->id;
            }
            $info .= "\n";
            echo $info;
            fwrite($writeFile, $info);
        }
    }
}
fclose($writeFile);
closedir($dir);
?>
