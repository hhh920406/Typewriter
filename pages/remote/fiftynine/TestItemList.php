<!DOCTYPE html>
<html>
    <head>
        <meta charset = UTF-8>
        <title>商品列表测试</title>
    </head>
    <body>
        <?php
        /**
         * 对商品列表的测试。
         * @author ZHG <CyberZHG@gmail.com>
         */
        require_once "DataSourceFiftynine.class.php";
        require_once "Test.php";
        $source = new DataSourceFiftynine();
        $result = $source->getItemList(-1, -1, "笔记本散热器");
        printArrayWithTable($result);
        ?>
    </body>
</html>
