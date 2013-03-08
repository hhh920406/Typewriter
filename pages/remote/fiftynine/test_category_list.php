<!DOCTYPE html>
<html>
    <head>
        <meta charset = UTF-8>
        <title>商品分类测试</title>
    </head>
    <body>
        <?php
        /**
         * 对商品分类的测试。
         * @author ZHG <CyberZHG@gmail.com>
         */
        require_once "DataSourceFiftynine.class.php";
        require_once "test.php";
        $source = new DataSourceFiftynine();
        $result = $source->getCategoryList();
        printArrayWithTable($result);
        //$result = $source->getCategoryList(19);
        //printArrayWithTable($result);
        ?>
    </body>
</html>


