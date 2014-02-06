<!DOCTYPE html>
<html>
    <head>
        <meta charset = UTF-8>
        <title>商家列表测试</title>
    </head>
    <body>
        <?php
        /**
         * 对卖家列表的测试。
         * @author ZHG <CyberZHG@gmail.com>
         */
        require_once "DataSourceFiftynine.class.php";
        require_once "test.php";
        $source = new DataSourceFiftynine();
        $result = $source->getSellerList();
        printArrayWithTable($result);
        ?>
    </body>
</html>


