<!DOCTYPE html>
<html>
    <head>
        <meta charset = UTF-8>
        <title>商家信息测试</title>
    </head>
    <body>
        <?php
        /**
         * 对商家信息的测试。
         * @author ZHG <CyberZHG@gmail.com>
         */
        require_once "DataSourceFiftynine.class.php";
        require_once "Test.php";
        $source = new DataSourceFiftynine();
        $result = $source->getSeller(1001);
        printArrayWithTable($result);
        ?>
    </body>
</html>


